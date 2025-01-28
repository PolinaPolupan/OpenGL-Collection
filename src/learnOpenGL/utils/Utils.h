#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Texture.h" 
#include "Lights.h"

unsigned int LoadCubemap(std::vector<std::string> faces);

std::string GetLightTypeName(LightType lightType);

LightType GetLightTypeByName(std::string name);

std::vector<std::string> GetTexturesPath(const std::vector<std::string>& extensions = { ".jpeg", ".jpg", ".png" }, const std::vector<std::string>& paths = { "res/textures" });

std::vector<std::string> GetObjectsPath();

std::vector<std::shared_ptr<Texture>> GetTextures(const std::vector<std::string>& extensions = { ".jpeg", ".jpg", ".png" }, const std::vector<std::string>& paths = { "res/textures" });

static void LoadTexturesFromPath(const std::filesystem::path& path, std::vector<std::string>& textures, const std::vector<std::string>& extensions);