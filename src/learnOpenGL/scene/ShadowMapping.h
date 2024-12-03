#pragma once

#include "pch.h"

namespace scene
{
	class ShadowMapping: public Scene
	{
	public:
		ShadowMapping();
		~ShadowMapping();

		std::shared_ptr<VertexArray> planeVAO, cubeVAO, quadVAO;
		std::shared_ptr<IndexBuffer> planeIBO, cubeIBO, quadIBO;
		std::shared_ptr<VertexBuffer> planeVBO, cubeVBO, quadVBO;
		std::shared_ptr<Shader> shader, simpleDepthShader, debugDepthQuad;
		std::shared_ptr<Texture> texture;

		CameraController cameraController;
		Renderer renderer;

		glm::vec3 lightPos = glm::vec3(-2.0f, 4.0f, -1.0f);

		const unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;
		unsigned int depthMapFBO, depthMap;
		bool debug = false;

		void OnUpdate(float deltaTime) override;
		void OnMouseMovedEvent(double posX, double posY) override;
		void OnMouseScrolledEvent(double offsetX, double offsetY) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;

		void RenderScene(std::shared_ptr<Shader> shader);
		void RenderQuad();
	};
}