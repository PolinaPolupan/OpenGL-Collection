#pragma once

#include "pch.h"

namespace scene
{
	class Blending : public Scene
	{
	public:
		Blending();
		~Blending();

		VertexArray cubeVAO, planeVAO, transparentVAO;
		std::unique_ptr<IndexBuffer> cubeIBO, planeIBO, transparentIBO;
		Texture cubeTexture, floorTexture, transparentTexture, windowTexture;
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
