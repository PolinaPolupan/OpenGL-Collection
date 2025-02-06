#include "Model.h"
#include "Shader.h"
#include "Mesh.h"
#include <filesystem>
#include <glad/glad.h> 
#include "Utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

Model::Model(const char* path):
    isSelected(false),
    isHidden(false),
    position(glm::vec3(0.f)),
    scale(glm::vec3(1.f))
{
    name = std::filesystem::path(path).filename().string();
    m_Directory = std::filesystem::path(path).parent_path().string() + "\\";
}

Model::Model(const std::filesystem::path& path):
    isSelected(false),
    isHidden(false),
    position(glm::vec3(0.f)),
    scale(glm::vec3(1.f))
{
    name = path.filename().string();
    m_Directory = std::filesystem::path(path).parent_path().string() + "\\";
}

Model::Model(): Model("") {}

void Model::LoadModel(const std::filesystem::path& path)
{
    LoadModel(path.string());
}

void Model::LoadModel(const std::string& path)
{
    name = std::filesystem::path(path).filename().string();

    const aiScene* scene = m_Importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << m_Importer.GetErrorString() << std::endl;
        return;
    }
    m_Directory = std::filesystem::path(path).parent_path().string() + "\\";

    ProcessNode(scene->mRootNode, scene);

    std::cout << "Textures size: " << m_TexturesLoaded.size() << "\n";
}

void Model::LoadModel()
{
    const aiScene* scene = m_Importer.ReadFile(name, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << m_Importer.GetErrorString() << std::endl;
        return;
    }
    m_Directory = std::filesystem::path(name).parent_path().string() + "\\";

    ProcessNode(scene->mRootNode, scene);

    std::cout << "Textures size: " << m_TexturesLoaded.size() << "\n";
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_Meshes.push_back(ProcessMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        std::cout << "SUCCESS::ASSIMP::PROCESSED:" << i << std::endl;
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    // data to fill
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<shared_ptr<Texture>> textures;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;
            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

  

    std::vector<std::shared_ptr<Texture>> defaultMaps = LoadMaterialTextures(material, aiTextureType_NONE, Texture::Type::Diffuse);
    textures.insert(textures.end(), defaultMaps.begin(), defaultMaps.end());

    std::vector<std::shared_ptr<Texture>> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, Texture::Type::Diffuse);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<std::shared_ptr<Texture>> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, Texture::Type::Specular);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<std::shared_ptr<Texture>>  normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, Texture::Type::Normal);
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<std::shared_ptr<Texture>> heightMaps = LoadMaterialTextures(material, aiTextureType_DISPLACEMENT, Texture::Type::Height);
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    

    return Mesh(vertices, indices, textures);
}

std::vector<std::shared_ptr<Texture>> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, Texture::Type typeName)
{
    std::vector<std::shared_ptr<Texture>> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        if (m_TexturesLoaded.find(str.C_Str()) != m_TexturesLoaded.end())
            textures.push_back(m_TexturesLoaded[str.C_Str()]);
        else
        {
            std::shared_ptr<Texture> texture = std::make_shared<Texture>(m_Directory + std::string(str.C_Str()), typeName);
            std::cout << std::string(str.C_Str()) << " type: " << texture->GetTextureTypeName() << "\n";
            textures.push_back(texture);
            m_TexturesLoaded[str.C_Str()]  = texture;
        }
    }

    return textures;
}
