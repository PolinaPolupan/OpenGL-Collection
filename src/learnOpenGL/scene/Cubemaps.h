#pragma once

#include "pch.h"

namespace scene
{
	class Cubemaps : public Scene
	{
	public:
		Cubemaps();
		~Cubemaps();

		unsigned int cubemapTexture;

		VertexArray cubeVAO, skyboxVAO;
		std::shared_ptr<VertexBuffer> cubeVBO, skyboxVBO;
		std::shared_ptr<IndexBuffer> cubeIBO, skyboxIBO;
		Texture cubeTexture;
		Shader shader, skyboxShader;

		CameraController cameraController;
		Renderer renderer;
		ObjectManager objectManager;
		std::vector<std::string> modelsPaths;

		void OnUpdate(float deltaTime) override;
		void OnMouseMovedEvent(double posX, double posY) override;
		void OnMouseScrolledEvent(double offsetX, double offsetY) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;
	};
}