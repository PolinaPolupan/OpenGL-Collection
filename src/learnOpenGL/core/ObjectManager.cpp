#include "ObjectManager.h"

ObjectManager::~ObjectManager()
{
	Clear();
}

void ObjectManager::AddObject(const std::string& path)
{
	std::shared_ptr<Model> model = std::make_shared<Model>(path.c_str());
	model->LoadModel(path);
	m_ObjectsToAdd.push_back(model);
}

void ObjectManager::DeleteObject(const int& n)
{
	if (n < m_Objects.size() && n > -1) {
		m_ObjectsToDelete.push_back(n);
	}
}

void ObjectManager::Update()
{
	std::sort(m_ObjectsToDelete.rbegin(), m_ObjectsToDelete.rend());
	for (auto& index : m_ObjectsToDelete) {
		m_Objects.erase(m_Objects.begin() + index);
	}
	for (auto& o : m_ObjectsToAdd)
	{
		m_Objects.push_back(o);
	}
	m_ObjectsToAdd.clear();
	m_ObjectsToDelete.clear();

	if (current_selected_object < 0) current_selected_object = 0;
	if (current_selected_object > m_Objects.size() - 1) current_selected_object = m_Objects.size() - 1;
}

void ObjectManager::Clear()
{
	m_ObjectsToAdd.clear();
	m_Objects.clear();
}

