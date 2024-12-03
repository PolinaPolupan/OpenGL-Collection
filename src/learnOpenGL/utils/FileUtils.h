#pragma once

#include <filesystem>
#include <string>

std::filesystem::path GetProjectDir();

std::filesystem::path GetResourcePath(const std::string& path);

static bool HasExtension(const std::string& filePath, const std::string& ext);