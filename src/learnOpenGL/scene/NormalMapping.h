#pragma once

#include "pch.h"

namespace scene
{
	class NormalMapping: public Scene
	{
	public:
		NormalMapping();
		~NormalMapping();

		std::shared_ptr<VertexArray> planeVAO;
		std::shared_ptr<IndexBuffer> planeIBO;
		std::shared_ptr<VertexBuffer> planeVBO;
		std::shared_ptr<Shader> planeShader;
		std::shared_ptr<Texture> diffuseMap, normalMap;

		glm::vec3 lightPos = glm::vec3(0.5f, 1.0f, 0.3f);

		ObjectManager objectManager;
		std::vector<std::string> modelsPaths;

		CameraController cameraController;
		Renderer renderer;

		void OnUpdate(float deltaTime) override;
		void OnMouseMovedEvent(double posX, double posY) override;
		void OnMouseScrolledEvent(double offsetX, double offsetY) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;
		void RenderPlane();
	};
}