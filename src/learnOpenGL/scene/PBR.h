#pragma once

#include "pch.h"
#include <random>

namespace scene
{
	class PBR: public Scene
	{
	public:
		PBR();
		~PBR();

		std::shared_ptr<VertexArray> sphereVAO;
		std::shared_ptr<IndexBuffer> sphereIBO;
		std::shared_ptr<VertexBuffer> sphereVBO;
		std::shared_ptr<Shader> shader;

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

		void OnUpdate(float deltaTime) override;
		void OnMouseMovedEvent(double posX, double posY) override;
		void OnMouseScrolledEvent(double offsetX, double offsetY) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;
	};
}
