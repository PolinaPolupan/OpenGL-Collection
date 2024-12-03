#pragma once

#include "pch.h"

namespace scene
{
	class AdvancedLighting: public Scene
	{
	public:
		AdvancedLighting();
		~AdvancedLighting();

		std::shared_ptr<VertexArray> planeVAO;
		std::shared_ptr<IndexBuffer> planeIBO;
		std::shared_ptr<VertexBuffer> planeVBO;
		std::shared_ptr<Shader> shader;
		std::shared_ptr<Texture> texture;

		CameraController cameraController;
		Renderer renderer;

		glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
		enum Mode { PHONG, BLIN_PHONG } mode;

		void OnUpdate(float deltaTime) override;
		void OnMouseMovedEvent(double posX, double posY) override;
		void OnMouseScrolledEvent(double offsetX, double offsetY) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;
	};
}
