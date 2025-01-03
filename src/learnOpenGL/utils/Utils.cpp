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
unsigned int loadCubemap(std::vector<std::string> faces)
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

std::string getLightTypeName(LightType lightType)
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

LightType getLightTypeByName(std::string name)
{
    if (name == "Spot") return LightType::Spot;
    if (name == "Directional") return LightType::Directional;
    if (name == "Point") return LightType::Point;
    return LightType::Default;
}

std::vector<std::string> getTexturesPath()
{
    std::vector<std::string> textures;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(GetResourcePath("res/textures")))
    {
        std::string path = entry.path().string();

        if (path.find(".jpeg") != std::string::npos || path.find(".jpg") != std::string::npos || path.find(".png") != std::string::npos) {
            std::cout << path << std::endl;
            textures.push_back(path);
        }
    }

    return textures;
}

std::vector<std::string> getObjectsPath()
{
    std::vector<std::string> objects;

    for (auto& p : std::filesystem::recursive_directory_iterator(GetResourcePath("res/objects")))
    {
        if (p.path().extension().string() == ".obj" || p.path().extension().string() == ".fbx")
        {
            std::cout << p.path().string() << '\n';
            objects.push_back(p.path().string());
        }
    }

    return objects;
}

std::vector<std::unique_ptr<Texture>> getTextures()
{
    std::vector<std::unique_ptr<Texture>> textures;
    for (auto& path : getTexturesPath())
    {
        textures.push_back(std::make_unique<Texture>(path, TextureType::Standard));
    }

    return textures;
}
