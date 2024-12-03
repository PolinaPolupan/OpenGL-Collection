#include "ClearColor.h"

scene::ClearColor::ClearColor()
	: m_ClearColor { 0.2f, 0.3f, 0.8f, 1.0f }
{

}

scene::ClearColor::~ClearColor()
{
}

void scene::ClearColor::OnUpdate(float deltaTime)
{
}

void scene::ClearColor::OnRender()
{
	GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void scene::ClearColor::OnImGuiRender()
{
	ImGui::ColorEdit4("Clear", m_ClearColor);
}
