#pragma once

#include "pch.h"

namespace scene
{
	class AdvancedGLSL: public Scene
	{
	public:
		AdvancedGLSL();
		~AdvancedGLSL();

		VertexArray cubeVAO;
		std::shared_ptr<IndexBuffer> cubeIBO;
		std::shared_ptr<VertexBuffer> cubeVBO;
		Shader shaderRed, shaderGreen, shaderBlue, shaderYellow;

		CameraController cameraController;
		Renderer renderer;

		unsigned int uboMatrices;
		glm::mat4 projection;
		unsigned int uniformBlockIndexRed, uniformBlockIndexGreen, uniformBlockIndexBlue, uniformBlockIndexYellow;

		void OnUpdate(float deltaTime) override;
		void OnMouseMovedEvent(double posX, double posY) override;
		void OnMouseScrolledEvent(double offsetX, double offsetY) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;
	};
}