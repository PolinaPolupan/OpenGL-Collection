#pragma once

#include "pch.h"

namespace scene
{
	class GeometryShader: public Scene
	{
	public:
		GeometryShader();
		~GeometryShader();

		std::shared_ptr<VertexArray> VAO;
		std::shared_ptr<VertexBuffer> VBO;
		std::shared_ptr<Shader> houseShader, explodeShader, defaultShader, normalShader;

		ObjectManager objectManager;
		std::vector<std::string> modelsPaths;
		CameraController cameraController;
		Renderer renderer;

		float magnitude = 0.2f;

		void OnUpdate(float deltaTime) override;
		void OnMouseMovedEvent(double posX, double posY) override;
		void OnMouseScrolledEvent(double offsetX, double offsetY) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;
	private:
		enum Mode { HOUSES, EXPLODE, NORMALS } mode;
		void OnRenderHouses();
		void OnRenderExplode();
		void OnRenderNormals();
	};
}