#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Texture.h" 
#include "Lights.h"

unsigned int loadCubemap(std::vector<std::string> faces);

std::string getLightTypeName(LightType lightType);

LightType getLightTypeByName(std::string name);

std::vector<std::string> getTexturesPath(const std::vector<std::string>& extensions = {".jpeg", ".jpg", ".png"});

std::vector<std::string> getObjectsPath();

std::vector<std::unique_ptr<Texture>> getTextures(const std::vector<std::string>& extensions = { ".jpeg", ".jpg", ".png" });
