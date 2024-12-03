#pragma once

#include <vector>
#include <functional>
#include <string>
#include <iostream>

namespace scene {

	class Scene
	{
	public:
		Scene() {}
		virtual ~Scene() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnEvent(int Event) {}
		virtual void OnMouseMovedEvent(double posX, double posY) {}
		virtual void OnMouseScrolledEvent(double offsetX, double offsetY) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class SceneMenu : public Scene
	{
	public:
		SceneMenu(Scene*& currentScene) :
			m_CurrentScene(currentScene) {}
		~SceneMenu() {};

		void OnImGuiRender() override;

		template<typename T>
		void RegisterScene(const std::string& name)
		{
			std::cout << "Registering scene " << name << "\n";
			m_Scenes.push_back(std::make_pair(name, []() { return new T(); }));
		}

	private:
		Scene*& m_CurrentScene;
		std::vector<std::pair<std::string, std::function<Scene*()>>> m_Scenes;
	}; 
}