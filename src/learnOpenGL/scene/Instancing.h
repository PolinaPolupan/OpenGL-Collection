#pragma once

#include "pch.h"

namespace scene
{
	class Instancing : public Scene
	{
	public:
		Instancing();
		~Instancing();

		std::shared_ptr<VertexArray> quadVAO;
		std::shared_ptr<VertexBuffer> quadVBO;
		std::shared_ptr<Shader> instanceShader, asteroidsShader, planetShader;
		std::shared_ptr<VertexBuffer> instanceVBO;

		CameraController cameraController;
		Renderer renderer;

		std::vector<glm::vec2> translations;
		std::vector<glm::mat4> modelMatrices;
		std::shared_ptr <Model> rock, planet;
		int amount = 2000;
		unsigned int buffer;
		float radius = 50.0;
		float offset = 2.5f;

		void OnUpdate(float deltaTime) override;
		void OnMouseMovedEvent(double posX, double posY) override;
		void OnMouseScrolledEvent(double offsetX, double offsetY) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;
	private:
		enum Mode { QUADS, ASTEROIDS } mode;
		void OnRenderAsteroids();
		void OnRenderQuads();
		void initAsteroidModelMatrices();
		void reloadAsteroids();
	};
}