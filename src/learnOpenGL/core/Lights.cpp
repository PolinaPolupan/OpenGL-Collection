#include "Lights.h"

LightManager::~LightManager()
{
    clear();
}

void LightManager::addLight(LightType tag)
{
    auto light = std::make_shared<Light>(light_nId, tag);
    m_lightsToAdd.push_back(light); 
    light_nId++;
}

void LightManager::update()
{
    for (auto& light : m_lightsToAdd)
    {
        m_lightsMap[light->getType()].push_back(light);
        m_lights.push_back(light);
    }
    for (auto& e : m_lightsMap)
    {
        auto toRemove = std::remove_if(m_lightsMap[e.first].begin(), m_lightsMap[e.first].end(), [](std::shared_ptr<Light> node) { return node->isActive() == false; });
        m_lightsMap[e.first].erase(toRemove, m_lightsMap[e.first].end());
    }

    auto to_remove = std::remove_if(m_lights.begin(), m_lights.end(), [](std::shared_ptr<Light> l) {return l->isActive() == false; });
    m_lights.erase(to_remove, m_lights.end());

    m_lightsToAdd.clear();
}

void LightManager::clear()
{
    m_lightsToAdd.clear();
    m_lights.clear();
    light_nId = 0;
}

