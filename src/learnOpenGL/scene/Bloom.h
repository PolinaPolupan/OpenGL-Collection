#pragma once

#include "pch.h"

namespace scene
{
	class Bloom: public Scene
	{
	public:
		Bloom();
		~Bloom();

		std::shared_ptr<VertexArray> quadVAO, cubeVAO;
		std::shared_ptr<IndexBuffer> quadIBO, cubeIBO;
		std::shared_ptr<VertexBuffer> quadVBO, cubeVBO;
		std::shared_ptr<Shader> shader, shaderLight, shaderBlur, shaderBloomFinal;
		std::shared_ptr<Texture> woodTexture, containerTexture;

		std::vector<glm::vec3> lightPositions, lightColors;

		unsigned int hdrFBO, colorBuffer, rboDepth;
		unsigned int colorBuffers[2];
		unsigned int pingpongFBO[2];
		unsigned int pingpongColorbuffers[2];
		unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };

		bool bloom = true;
		float threshold = 1.f;
		float mu = 0.2f;
		float exposure = 1.0f;
		int kernelSize = 5;
		int amount = 10;

		CameraController cameraController;
		Renderer renderer;

		void OnUpdate(float deltaTime) override;
		void OnMouseMovedEvent(double posX, double posY) override;
		void OnMouseScrolledEvent(double offsetX, double offsetY) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;
	};
}