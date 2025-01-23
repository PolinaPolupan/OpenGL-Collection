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
		std::shared_ptr<Texture> albedo, normal, metallic, roughness, ao, hdr;
		std::vector<std::unique_ptr<Texture>> textures;

		glm::vec3 lightPos = glm::vec3(2.0, 4.0, -2.0);
		glm::vec3 lightColor = glm::vec3(0.2, 0.2, 0.7);

		CameraController cameraController;
		Renderer renderer;

		// lights
		std::vector<glm::vec3> lightPositions;
		std::vector<glm::vec3> lightColors;

		int nrRows = 7;
		int nrColumns = 7;
		float spacing = 2.5;

		unsigned int indexCount;
		bool textured = false;

		unsigned int captureFBO;
		unsigned int captureRBO;
		unsigned int envCubemap;
		unsigned int irradianceMap;
		unsigned int prefilterMap;
		unsigned int brdfLUTTexture;

		float transparency = 0.0f;

		void OnUpdate(float deltaTime) override;
		void OnMouseMovedEvent(double posX, double posY) override;
		void OnMouseScrolledEvent(double offsetX, double offsetY) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;
	};
}