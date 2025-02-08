#pragma once

#include "pch.h"


namespace scene
{
	class SkeletalAnimation: public Scene
	{
	public:
		SkeletalAnimation();
		~SkeletalAnimation();

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