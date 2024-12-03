#pragma once

#include "pch.h"

namespace scene {
	class ClearColor : public Scene
	{
	public:
		ClearColor();
		~ClearColor();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float m_ClearColor[4];
	};
}