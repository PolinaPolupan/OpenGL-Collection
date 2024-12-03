#pragma once

#include "pch.h"

namespace scene
{
	class GammaCorrection: public Scene
	{
	public:
		GammaCorrection();
		~GammaCorrection();

		std::shared_ptr<VertexArray> planeVAO;
		std::shared_ptr<IndexBuffer> planeIBO;
		std::shared_ptr<VertexBuffer> planeVBO;
		std::shared_ptr<Shader> shader;
		std::shared_ptr<Texture> texture, textureGammaCorrected;

		CameraController cameraController;
		Renderer renderer;

		glm::vec3 lightPositions[4] = { 
			glm::vec3(-3.0f, 0.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(3.0f, 0.0f, 0.0f) 
		};
		glm::vec3 lightColors[4] = {
			glm::vec3(0.25),
			glm::vec3(0.50),
			glm::vec3(0.75),
			glm::vec3(1.00)
		};

		bool gammaEnabled = false;

		void OnUpdate(float deltaTime) override;
		void OnMouseMovedEvent(double posX, double posY) override;
		void OnMouseScrolledEvent(double offsetX, double offsetY) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;
	};
}