#pragma once

#include "pch.h"

namespace scene
{
	class Framebuffers : public Scene
	{
	public:
		Framebuffers();
		~Framebuffers();

		unsigned int textureColorbuffer;
		unsigned int framebuffer;
		unsigned int rbo;
		int matrixSize = 900;
		float matrix[9] = {0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f};

		VertexArray cubeVAO, planeVAO, quadVAO;
		std::shared_ptr<VertexBuffer> cubeVBO, planeVBO, quadVBO;
		std::shared_ptr<IndexBuffer> cubeIBO, planeIBO, quadIBO;
		Texture cubeTexture, planeTexture;
		Shader shader, screenShader;

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
