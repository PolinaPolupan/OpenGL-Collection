#pragma once

#include "pch.h"


namespace scene {
	class CoordinateSystem : public Scene
	{
	public:
		CoordinateSystem();
		~CoordinateSystem();

		void OnUpdate(float deltaTime) override;
		void OnMouseMovedEvent(double posX, double posY) override;
		void OnMouseScrolledEvent(double offsetX, double offsetY) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;
	private:
		float m_FOV;
		float m_NearClipRange;
		float m_FarClipRange;
		float m_CameraSpeed;
		CameraController m_cameraController;
		glm::mat4 m_Proj, m_View;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<VertexBuffer> m_VBO;
		glm::vec3 m_CubePositions[];
	};
}
