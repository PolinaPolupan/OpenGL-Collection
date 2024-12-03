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

void ObjectManager::update()
{
	for (auto& o : m_objectsToAdd)
	{
		m_objects.push_back(o);
	}
	m_objectsToAdd.clear();
}

void ObjectManager::clear()
{
	m_objectsToAdd.clear();
	m_objects.clear();
}

