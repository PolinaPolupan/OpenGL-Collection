#pragma once

#include "pch.h"

namespace scene {
	class ModelLoading : public Scene
	{
	public:
		ModelLoading();
		~ModelLoading();

		Model model;
		Shader shader;
		Shader selection;
		CameraController cameraController;
		Renderer renderer;

		LightManager lightManager;
		ObjectManager objectManager;


		void OnUpdate(float deltaTime) override;
		void OnMouseMovedEvent(double posX, double posY) override;
		void OnMouseScrolledEvent(double offsetX, double offsetY) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnEvent(int event) override;
	private:
		std::vector<std::string> m_ModelsPaths;
	};
};
