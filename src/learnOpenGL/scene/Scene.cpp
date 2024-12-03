#include "Scene.h"
#include "imgui.h"

void scene::SceneMenu::OnImGuiRender()
{
	for (auto& scene : m_Scenes)
	{
		if (ImGui::Button(scene.first.c_str()))
			m_CurrentScene = scene.second();
	}
}
