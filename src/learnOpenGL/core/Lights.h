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

class Light: public Node
{
public:
    Light(unsigned int id, LightType type): 
        Node(id), 
        m_Type(type),
        isEnabled(true),
        color(glm::vec3(1.f, 1.f, 1.f)),
        position(glm::vec3(0.f)),
        direction(glm::vec3(0.f)),
        intensity(1.0f),
        cutOff(12.5f),
        outerCutOff(17.5f),
        constant(1.0f),
        linear(0.09f),
        quadratic(0.032f)
    {
        m_CashedIntensity = intensity;
        m_Shader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\Light.shader"));
        m_Model = std::make_shared<Model>();
        m_Model->LoadModel(GetResourcePath("res\\objects\\light\\sphere.obj"));
        m_Model->scale = glm::vec3(0.1f);
    }
 
    void TriggerEnable() {
        if (!isEnabled) Disable();
        else Enable();
    }

    float GetIntensity() const {
        if (isEnabled) return intensity;
        return 0.f;
    }

    inline void ChangeType(LightType type) { m_Type = type; }

    std::shared_ptr<Shader>& GetShader() { return m_Shader; }

    Model& GetModel() { return *m_Model; }

    inline LightType GetType() const { return m_Type; }

public:
    bool isEnabled;
    glm::vec3 color;
    glm::vec3 position;
    float intensity = 1.f;
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;

private:
    void Enable() {
        m_Model->isHidden = false;
        intensity = m_CashedIntensity;
    }
    void Disable() {
        m_Model->isHidden = true;
        m_CashedIntensity = intensity;
        intensity = 0.f;
    }

private:
    std::shared_ptr<Shader> m_Shader;
    LightType m_Type = LightType::Default;
    std::shared_ptr<Model> m_Model;
    float m_CashedIntensity;
};

class LightManager
{
public:
    LightManager() {};
    ~LightManager();
   
    void AddLight(LightType tag);

    void Update();

    void Clear();

    std::vector<std::shared_ptr<Light>>& GetLightsByType(LightType type) { return m_LightsMap[type]; }

    std::vector <std::shared_ptr<Light>>& GetLights() { return m_Lights; }

private:
    int m_Light_nId = 0;
    std::vector <std::shared_ptr<Light>> m_Lights;
    std::map<LightType, std::vector <std::shared_ptr<Light>>> m_LightsMap;
    std::vector<std::shared_ptr<Light>> m_LightsToAdd;
};
