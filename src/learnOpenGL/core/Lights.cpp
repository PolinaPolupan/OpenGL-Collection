#include "Lights.h"

LightManager::~LightManager()
{
    Clear();
}

void LightManager::AddLight(LightType tag)
{
    auto light = std::make_shared<Light>(m_Light_nId, tag);
    m_LightsToAdd.push_back(light); 
    m_Light_nId++;
}

void LightManager::Update()
{
    for (auto& light : m_LightsToAdd)
    {
        m_LightsMap[light->GetType()].push_back(light);
        m_Lights.push_back(light);
    }
    for (auto& e : m_LightsMap)
    {
        auto toRemove = std::remove_if(m_LightsMap[e.first].begin(), m_LightsMap[e.first].end(), [](std::shared_ptr<Light> node) { return node->IsActive() == false; });
        m_LightsMap[e.first].erase(toRemove, m_LightsMap[e.first].end());
    }

    auto to_remove = std::remove_if(m_Lights.begin(), m_Lights.end(), [](std::shared_ptr<Light> l) {return l->IsActive() == false; });
    m_Lights.erase(to_remove, m_Lights.end());

    m_LightsToAdd.clear();
}

void LightManager::Clear()
{
    m_LightsToAdd.clear();
    m_Lights.clear();
    m_Light_nId = 0;
}

