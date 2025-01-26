#pragma once

#include "Texture.h"
#include <filesystem>

struct Material
{
	Material(): 
		diffuseColor(glm::vec3(1.f, 1.f, 1.f)),
		specularColor(glm::vec3(1.f, 1.f, 1.f)) {}

	std::unique_ptr<Texture> diffuseMap;
	std::unique_ptr<Texture> specularMap;
	std::unique_ptr<Texture> emissionMap;

	glm::vec3 diffuseColor;
	glm::vec3 specularColor;

	float emissionWeight = 0.f;
	float shininess = 0.f;

	void SetDiffuseMap(std::string path) {
		diffuseMap = std::make_unique<Texture>(path, TextureType::Diffuse);
		diffuseMap->Bind(0);
		diffuseColor = glm::vec3(1.f, 1.f, 1.f);
	}

	void SetDiffuseMap(const std::filesystem::path& path) {
		diffuseMap = std::make_unique<Texture>(path, TextureType::Diffuse);
		diffuseMap->Bind(0);
		diffuseColor = glm::vec3(1.f, 1.f, 1.f);
	}

	void SetSpecularMap(std::string path) {
		specularMap = std::make_unique<Texture>(path, TextureType::Specular);
		specularMap->Bind(1);
		specularColor = glm::vec3(1.f, 1.f, 1.f);
	}

	void SetSpecularMap(const std::filesystem::path& path) {
		specularMap = std::make_unique<Texture>(path, TextureType::Specular);
		specularMap->Bind(1);
		specularColor = glm::vec3(1.f, 1.f, 1.f);
	}

	void SetEmissionMap(std::string path) {
		emissionMap = std::make_unique<Texture>(path, TextureType::Emission);
		emissionMap->Bind(2);
	}

	void SetEmissionMap(const std::filesystem::path& path) {
		emissionMap = std::make_unique<Texture>(path, TextureType::Emission);
		emissionMap->Bind(2);
	}

	void SetDiffuseColor(glm::vec3 color) { diffuseColor = color; }

	void SetSpecularColor(glm::vec3 color) { specularColor = color; }
};
