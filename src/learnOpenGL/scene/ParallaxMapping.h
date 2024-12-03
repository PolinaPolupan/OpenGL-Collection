#pragma once

#include "pch.h"

namespace scene
{
	class ParallaxMapping : public Scene
	{
	public:
		ParallaxMapping();
		~ParallaxMapping();

		std::shared_ptr<VertexArray> planeVAO;
		std::shared_ptr<IndexBuffer> planeIBO;
		std::shared_ptr<VertexBuffer> planeVBO;
		std::shared_ptr<Shader> planeShader;
		std::shared_ptr<Texture> diffuseMap, normalMap, heightMap;

		glm::vec3 lightPos = glm::vec3(0.5f, 1.0f, 0.3f);

		ObjectManager objectManager;
		std::vector<std::string> modelsPaths;

		float heightScale = 0.01f;

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