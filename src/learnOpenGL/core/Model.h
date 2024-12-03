#pragma once

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <unordered_map>
#include "Texture.h"
#include "Constants.h"
#include "Material.h"
#include <filesystem>


class Model
{
public:
    Model(const char* path);
    Model(const std::filesystem::path& path);
    Model();

    std::string name;
    bool isSelected = false;
    bool isHidden = false;
    glm::vec3 position = glm::vec3(0.f);
    glm::vec3 scale = glm::vec3(1.f);
    void LoadModel(const std::filesystem::path& path);
    void LoadModel(std::string path);
    void LoadModel();
    std::vector<Mesh>& getMeshes() { return m_Meshes; }
    std::unordered_map<std::string, std::shared_ptr<Texture>>& getTexturesLoaded() { return m_TexturesLoaded; }

    Mesh& operator [] (unsigned int index) {
        return m_Meshes[index];
    }

private:
    Assimp::Importer m_Importer;
    std::vector<Mesh> m_Meshes;
    std::string m_Directory;
    std::unordered_map<std::string, std::shared_ptr<Texture>> m_TexturesLoaded;

    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<std::shared_ptr<Texture>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type,
        TextureType typeName);
};

