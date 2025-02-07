#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <unordered_map>
#include <filesystem>
#include <map>


class Mesh;
class Bone;
class Texture;

class Model
{
public:
    Model(const char* path);
    Model(const std::filesystem::path& path);
    Model();

    void LoadModel(const std::filesystem::path& path);
    void LoadModel(const std::string& path);
    void LoadModel();

    std::vector<Mesh>& GetMeshes() { return m_Meshes; }
    std::unordered_map<std::string, std::shared_ptr<Texture>>& GetTexturesLoaded() { return m_TexturesLoaded; }

    Mesh& operator[] (unsigned int index) { return m_Meshes[index]; }

public:
    std::string name;
    bool isSelected;
    bool isHidden;
    glm::vec3 position;
    glm::vec3 scale;

private:
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<std::shared_ptr<Texture>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, Texture::Type typeName);
    void ExtractBones(std::vector<Vertex>& vertices, aiMesh* mesh);

private:
    Assimp::Importer m_Importer;
    std::vector<Mesh> m_Meshes;
    std::string m_Directory;
    std::unordered_map<std::string, std::shared_ptr<Texture>> m_TexturesLoaded;

    std::map<std::string, Bone> m_BoneMap; 
    int m_BoneCounter = 0;
};

