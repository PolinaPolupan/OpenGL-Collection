#pragma once

#include "pch.h"

namespace scene
{
	class Antialiasing: public Scene
	{
	public:
		Antialiasing();
		~Antialiasing();

		std::shared_ptr<VertexArray> cubeVAO, quadVAO;
		std::shared_ptr<IndexBuffer> cubeIBO;
		std::shared_ptr<VertexBuffer> cubeVBO, quadVBO;
		std::shared_ptr<Shader> shader, screenShader;

		CameraController cameraController;
		Renderer renderer;

		unsigned int framebuffer;
		unsigned int textureColorBufferMultiSampled;
		unsigned int rbo;
		unsigned int intermediateFBO;
		unsigned int screenTexture;

		void OnUpdate(float deltaTime) override;
		void OnMouseMovedEvent(double posX, double posY) override;
		void OnMouseScrolledEvent(double offsetX, double offsetY) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;
	};
}