#pragma once

#include "pch.h"
#include <random>

namespace scene
{
	class SSAO: public Scene
	{
	public:
		SSAO();
		~SSAO();

		std::shared_ptr<VertexArray> quadVAO, cubeVAO;
		std::shared_ptr<IndexBuffer> quadIBO, cubeIBO;
		std::shared_ptr<VertexBuffer> quadVBO, cubeVBO;
		std::shared_ptr<Shader> shaderGeometryPass, shaderLightingPass, shaderSSAO, shaderSSAOBlur, shaderSSAOFlat;

		glm::vec3 lightPos = glm::vec3(2.0, 4.0, -2.0);
		glm::vec3 lightColor = glm::vec3(0.2, 0.2, 0.7);

		CameraController cameraController;
		Renderer renderer;
		ObjectManager objectManager;
		std::vector<std::string> modelsPaths;

		unsigned int gBuffer;
		unsigned int gPosition, gNormal, gAlbedo;
		unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
		unsigned int rboDepth;
		unsigned int ssaoFBO, ssaoBlurFBO;
		unsigned int ssaoColorBuffer, ssaoColorBufferBlur;
		unsigned int noiseTexture;

		std::vector<glm::vec3> ssaoKernel;
		std::vector<glm::vec3> ssaoNoise;

		bool light = true;
		bool blur = true;
		float radius = 0.5;
		float bias = 0.025;
		int samples = 64;

		void OnUpdate(float deltaTime) override;
		void OnMouseMovedEvent(double posX, double posY) override;
		void OnMouseScrolledEvent(double offsetX, double offsetY) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;
		void GenerateSamples();
	};
}
