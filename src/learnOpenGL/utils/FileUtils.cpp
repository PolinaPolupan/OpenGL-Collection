#include "FileUtils.h"

namespace fs = std::filesystem;

static bool HasExtension(const std::string& filePath, const std::string& ext) {
    
    fs::path path(filePath);
    return path.extension() == ext;
}


std::filesystem::path GetProjectDir() {

    return fs::current_path();
}

std::filesystem::path GetResourcePath(const std::string& path)
{
    std::filesystem::path baseDir = PROJECT_DIR;
    std::filesystem::path fullPath = baseDir / path;

    if (fs::exists(fullPath)) {
        return fullPath;
    }
    else {
        throw std::runtime_error("File not found: " + path);
    }

    throw std::runtime_error("File not found: " + fullPath.string());
}
