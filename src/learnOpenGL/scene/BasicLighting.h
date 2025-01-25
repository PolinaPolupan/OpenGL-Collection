#pragma once

#include "pch.h"

namespace scene {
	class BasicLighting : public Scene
	{
	public:
		Material material;
		glm::vec3 backgroundColor;
	
		LightManager lightManager;
		std::vector<std::shared_ptr<Texture>> textures;

		BasicLighting();
		~BasicLighting();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;
		void OnMouseMovedEvent(double posX, double posY) override;
	private:
	
		float m_CameraSpeed;
		CameraController m_cameraController;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VBO;
		glm::vec3 m_CubePositions[];
	};
}