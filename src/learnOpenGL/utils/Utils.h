#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Texture.h" 
#include "Lights.h"

unsigned int LoadCubemap(std::vector<std::string> faces);

std::string GetLightTypeName(LightType lightType);

LightType GetLightTypeByName(std::string name);

std::vector<std::string> GetResourcesPath(
	const std::vector<std::string>& extensions = { ".jpeg", ".jpg", ".png" },
	const std::vector<std::string>& paths = { "res/textures" },
	bool filenameOnly = false
);

std::vector<std::string> GetObjectsPath();

std::vector<std::shared_ptr<Texture>> GetTextures(
	const std::vector<std::string>& extensions = { ".jpeg", ".jpg", ".png" }, 
	const std::vector<std::string>& paths = { "res/textures" }
);

static void LoadResourcesFromPath(
	const std::filesystem::path& path, 
	std::vector<std::string>& resources, 
	const std::vector<std::string>& extensions,
	bool filenameOnly
);