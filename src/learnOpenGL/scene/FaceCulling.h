#pragma once

#include "pch.h"

namespace scene
{
	class FaceCulling : public Scene
	{
	public:
		FaceCulling();
		~FaceCulling();

		VertexArray cubeVAO, planeVAO;
		std::unique_ptr<IndexBuffer> cubeIBO, planeIBO;
		Texture cubeTexture;
		Shader shader;

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