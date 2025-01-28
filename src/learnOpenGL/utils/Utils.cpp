#pragma once

#include "Utils.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <memory>
#include "Constants.h"
#include "Texture.h"
#include "Material.h"  
#include "imgui.h"
#include "Lights.h"
#include "stb_image.h"
#include "FileUtils.h"


//// loads a cubemap texture from 6 individual texture faces
//// order:
//// +X (right)
//// -X (left)
//// +Y (top)
//// -Y (bottom)
//// +Z (front) 
//// -Z (back)
//// -------------------------------------------------------
unsigned int LoadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    stbi_set_flip_vertically_on_load(false);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

std::string GetLightTypeName(LightType lightType)
{
    switch (lightType)
    {
    case Spot:
        return "Spot";
    case Directional:
        return "Directional";
    case Point:
        return "Point";
    case Default:
        return "None";
    }
}

LightType GetLightTypeByName(std::string name)
{
    if (name == "Spot") return LightType::Spot;
    if (name == "Directional") return LightType::Directional;
    if (name == "Point") return LightType::Point;
    return LightType::Default;
}

std::vector<std::string> GetTexturesPath(const std::vector<std::string>& extensions, const std::vector<std::string>& paths)
{
    std::vector<std::string> textures;

    for (auto& path : paths) {
        LoadTexturesFromPath(GetResourcePath(path), textures, extensions);
    }
   
    return textures;
}

void LoadTexturesFromPath(const std::filesystem::path& path, std::vector<std::string>& textures, const std::vector<std::string>& extensions)
{
    for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
    {
        std::string path = entry.path().string();

        for (auto& ext : extensions) {
            if (path.find(ext) != std::string::npos) {
                std::cout << path << std::endl;
                textures.push_back(path);
                break;
            }
        }
    }
}

std::vector<std::string> GetObjectsPath()
{
    std::vector<std::string> objects;

    for (auto& p : std::filesystem::recursive_directory_iterator(GetResourcePath("res/objects")))
    {
        if (p.path().extension().string() == ".obj" || p.path().extension().string() == ".fbx" || p.path().extension().string() == ".FBX")
        {
            std::cout << p.path().string() << '\n';
            objects.push_back(p.path().string());
        }
    }

    return objects;
}

std::vector<std::shared_ptr<Texture>> GetTextures(const std::vector<std::string>& extensions, const std::vector<std::string>& paths)
{
    std::vector<std::shared_ptr<Texture>> textures;
    for (auto& path : GetTexturesPath(extensions, paths))
    {
        textures.push_back(std::make_unique<Texture>(path, TextureType::Standard));
    }

    return textures;
}
