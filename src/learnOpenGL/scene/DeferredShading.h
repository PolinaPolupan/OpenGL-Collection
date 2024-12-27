#pragma once

#include "pch.h"

namespace scene
{
	class DeferredShading: public Scene
	{
	public:
		DeferredShading();
		~DeferredShading();

		std::shared_ptr<VertexArray> quadVAO, cubeVAO;
		std::shared_ptr<IndexBuffer> quadIBO, cubeIBO;
		std::shared_ptr<VertexBuffer> quadVBO, cubeVBO;
		std::shared_ptr<Shader> shaderGeometryPass, shaderLightingPass, shaderLightBox, shaderFlat;

		std::vector<glm::vec3> lightPositions, lightColors;
		std::vector<glm::vec3> objectPositions;

		CameraController cameraController;
		Renderer renderer;
		ObjectManager objectManager;
		std::vector<std::string> modelsPaths;

		unsigned int gBuffer;
		unsigned int gPosition, gNormal, gAlbedoSpec;
		unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
		unsigned int rboDepth;

		bool light = true;
		int textureType = 0;

		void OnUpdate(float deltaTime) override;
		void OnMouseMovedEvent(double posX, double posY) override;
		void OnMouseScrolledEvent(double offsetX, double offsetY) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;
	};
}
