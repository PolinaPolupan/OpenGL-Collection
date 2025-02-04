#pragma once

#include "pch.h"

namespace scene
{
	class OIT: public Scene
	{
	public:
		OIT();
		~OIT();

		std::shared_ptr<VertexArray> quadVAO;
		std::shared_ptr<IndexBuffer> quadIBO;
		std::shared_ptr<VertexBuffer> quadVBO;
		std::shared_ptr<Shader> 
			solidShader, 
			transparentShader, 
			compositeShader,
			screenShader;
		std::shared_ptr<Texture> 
			opaqueTexture, 
			depthTexture,
			accumTexture, 
			revealTexture;

		CameraController cameraController;
		Renderer renderer;

		std::shared_ptr<Framebuffer> opaqueFBO, transparentFBO;

		ObjectManager objectManager;
		std::vector<std::string> modelsPaths;

		void OnUpdate(float deltaTime) override;
		void OnMouseMovedEvent(double posX, double posY) override;
		void OnMouseScrolledEvent(double offsetX, double offsetY) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;
	};
}