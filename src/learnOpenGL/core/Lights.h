#pragma once
#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "Model.h"
#include "Node.h"
#include "Shader.h"
#include <memory>
#include <map>
#include "FileUtils.h"

enum LightType
{
    Spot,
    Point,
    Directional,
    Default
};

class Light : public Node
{
public:

    Light(unsigned int id, LightType type) 
        : Node(id), m_Type(type)
    {
        m_cashedIntensity = intensity;
        m_Shader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\Light.shader"));
        m_Model = std::make_shared<Model>();
        m_Model->LoadModel(GetResourcePath("res\\objects\\light\\sphere.obj"));
        m_Model->scale = glm::vec3(0.1f);
    }
 
    bool isEnabled = true;
    glm::vec3 color = glm::vec3(1.f, 1.f, 1.f);
    glm::vec3 position = glm::vec3(0.f);

    float intensity = 1.f; // can't make it private, because it's used in ImGui

    glm::vec3 direction = glm::vec3(0.f);
    float cutOff = 12.5f;
    float outerCutOff = 17.5f;

    float constant = 1.f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    void triggerEnable()
    {
        if (!isEnabled)
        {
            disable();
        }
        else
        {
            enable();
        }
    }

    float getIntensity() const 
    {
        if (isEnabled)
            return intensity;
        else
            return 0.f;
    }

    inline void changeType(LightType type) { m_Type = type; }

    std::shared_ptr<Shader>& getShader() { return m_Shader; }
    Model& getModel() { return *m_Model; }
    inline LightType getType() const { return m_Type; }

private:
    std::shared_ptr<Shader> m_Shader;
    LightType m_Type = LightType::Default;
    std::shared_ptr<Model> m_Model;
    
    float m_cashedIntensity;

    void enable()
    {
        m_Model->isHidden = false;
        intensity = m_cashedIntensity;
    }
    void disable()
    {
        m_Model->isHidden = true;
        m_cashedIntensity = intensity;
        intensity = 0.f;
    }
};

class LightManager
{
public:
    LightManager() {};
    ~LightManager();
    int light_nId = 0;

    void addLight(LightType tag);

    void update();

    void clear();

    std::vector<std::shared_ptr<Light>>& getLightsByType(LightType type)
    {
        return m_lightsMap[type];
    }

    std::vector <std::shared_ptr<Light>>& getLights()
    {
        return m_lights;
    }

private:
    std::vector <std::shared_ptr<Light>> m_lights;
    std::map<LightType, std::vector <std::shared_ptr<Light>>> m_lightsMap;
    std::vector<std::shared_ptr<Light>> m_lightsToAdd;
};
