#include "ObjectManager.h"

ObjectManager::~ObjectManager()
{
	clear();
}

void ObjectManager::addObject(std::string& path)
{
	std::shared_ptr<Model> model = std::make_shared<Model>(path.c_str());
	model->LoadModel(path);
	m_objectsToAdd.push_back(model);
}

void ObjectManager::deleteObject(const int& n)
{
	if (n < m_objects.size() && n > -1) {
		m_objectsToDelete.push_back(n);
	}
}

void ObjectManager::update()
{
	std::sort(m_objectsToDelete.rbegin(), m_objectsToDelete.rend());
	for (auto& index : m_objectsToDelete) {
		m_objects.erase(m_objects.begin() + index);
	}
	for (auto& o : m_objectsToAdd)
	{
		m_objects.push_back(o);
	}
	m_objectsToAdd.clear();
	m_objectsToDelete.clear();

	if (current_selected_object < 0) current_selected_object = 0;
	if (current_selected_object > m_objects.size() - 1) current_selected_object = m_objects.size() - 1;
}

void ObjectManager::clear()
{
	m_objectsToAdd.clear();
	m_objects.clear();
}

