#pragma once

#include "pch.h"

namespace scene
{
	class Hdr: public Scene
	{
	public:
		Hdr();
		~Hdr();

		std::shared_ptr<VertexArray> planeVAO, cubeVAO;
		std::shared_ptr<IndexBuffer> planeIBO, cubeIBO;
		std::shared_ptr<VertexBuffer> planeVBO, cubeVBO;
		std::shared_ptr<Shader> shader, hdrShader;
		std::shared_ptr<Texture> woodTexture;

		std::vector<glm::vec3> lightPositions, lightColors;

		unsigned int hdrFBO, colorBuffer, rboDepth;
		
		float degress = 90.f;
		bool hdr = true;
		float exposure = 1.0f;

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