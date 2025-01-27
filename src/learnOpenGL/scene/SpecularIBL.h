#pragma once

#include "pch.h"
#include <random>

namespace scene
{
	class SpecularIBL: public Scene
	{
	public:
		SpecularIBL();
		~SpecularIBL();

		std::shared_ptr<VertexArray> sphereVAO, cubeVAO, quadVAO;
		std::shared_ptr<IndexBuffer> sphereIBO, cubeIBO, quadIBO;
		std::shared_ptr<VertexBuffer> sphereVBO, cubeVBO, quadVBO;
		std::shared_ptr<Shader> 
			pbrShader, 
			shaderTextured, 
			equirectangularToCubemapShader, 
			backgroundShader, 
			irradianceShader,
			prefilterShader,
			brdfShader;
		std::shared_ptr<Texture> 
			albedoTexture, 
			normalTexture, 
			metallicTexture, 
			roughnessTexture, 
			aoTexture, 
			hdr,
			brdfLUTTexture,
			envCubemapTexture,
			irradianceMapTexture,
			prefilterMapTexture;
		std::vector<std::shared_ptr<Texture>> textures;
		std::vector<std::shared_ptr<Texture>> mapTextures;

		glm::vec3 albedoColor;

		CameraController cameraController;
		Renderer renderer;

		// lights
		std::vector<glm::vec3> lightPositions;
		std::vector<glm::vec3> lightColors;


		unsigned int indexCount;
		bool textured = false;

		unsigned int captureFBO;
		unsigned int captureRBO;

		float transparency = 0.0f;
		float roughness = 0.5f;
		float metallic = 0.0f;
		float ao = 1.0f;

		void OnUpdate(float deltaTime) override;
		void OnMouseMovedEvent(double posX, double posY) override;
		void OnMouseScrolledEvent(double offsetX, double offsetY) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;
		
		void BakeMaps();
		void MapBrowser(std::shared_ptr<Texture>& texture);
		void InvokeMapBrowser(std::shared_ptr<Texture>& texture);
	};
}