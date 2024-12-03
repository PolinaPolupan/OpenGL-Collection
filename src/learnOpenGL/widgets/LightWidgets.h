#pragma once

#include "imgui.h"
#include "Lights.h"
#include "Utils.h"


static void pointLightUi(Light& pointLight)
{
    if (ImGui::Checkbox("Enable", &pointLight.isEnabled))
    {
        if (pointLight.intensity == 0.f)
            pointLight.triggerEnable();
    }
    ImGui::SliderFloat3("Light Position", &pointLight.getModel().position[0], -20.f, 20.f);
    ImGui::SliderFloat("Intensity", &pointLight.intensity, 0.f, 100.f);
    ImGui::ColorEdit3("Light color", &pointLight.color[0]);
}

static void directionalLightUi(Light& dirlight)
{
    if (ImGui::Checkbox("Enable", &dirlight.isEnabled))
    {
        if (dirlight.intensity == 0.f)
            dirlight.triggerEnable();
    }
    ImGui::SliderFloat3("Light Direction", &dirlight.direction[0], -20.f, 20.f);
    ImGui::SliderFloat("Intensity", &dirlight.intensity, 0.f, 100.f);
    ImGui::ColorEdit3("Light color", &dirlight.color[0]);
}

static void spotLightUi(Light& spotlight)
{
    if (ImGui::Checkbox("Enable", &spotlight.isEnabled))
    {
        if (spotlight.intensity == 0.f)
            spotlight.triggerEnable();
    }
    ImGui::SliderFloat3("Light Direction", &spotlight.direction[0], -20.f, 20.f);
    ImGui::SliderFloat3("Light Position", &spotlight.getModel().position[0], -20.f, 20.f);
    ImGui::SliderFloat("Inner cut off", &spotlight.cutOff, 0.f, 90.f);
    ImGui::SliderFloat("Outer cut off", &spotlight.outerCutOff, 0.f, 90.f);
    ImGui::SliderFloat("Intensity", &spotlight.intensity, 0.f, 100.f);
    ImGui::ColorEdit3("Light color", &spotlight.color[0]);
}

static void LightsTabBar(std::vector<std::shared_ptr<Light>>& lights)
{
    if (lights.size() != 0)
    {
        int i = 0;
        if (ImGui::BeginTabBar("Lights", ImGuiTabBarFlags_None))
        {
            for (auto& light : lights)
            {
                if (ImGui::BeginTabItem(("light_" + std::to_string(i)).c_str()))
                {
                    ImGui::Text(("light_" + std::to_string(i)).c_str());
                    std::string items[] = { getLightTypeName(LightType::Spot), getLightTypeName(LightType::Point), getLightTypeName(LightType::Directional) };
                   
                    static int item_current_idx = lights[i]->getType(); // Here we store our selection data as an index.

                    // Pass in the preview value visible before opening the combo (it could technically be different contents or not pulled from items[])
                    std::string combo_preview_value = items[lights[i]->getType()];

                    if (ImGui::BeginCombo("Type", combo_preview_value.c_str()))
                    {
                        for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                        {
                            const bool is_selected = (item_current_idx == n);
                            if (ImGui::Selectable(items[n].c_str(), is_selected))
                            {
                                item_current_idx = n;
                                lights[i]->changeType((LightType)item_current_idx);
                            }
                            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                            if (is_selected)
                                ImGui::SetItemDefaultFocus();
                        }
                        ImGui::EndCombo();
                    }
                    switch ((LightType)item_current_idx)
                    {
                    case LightType::Spot:
                        spotLightUi(*lights[i]);
                        break;
                    case LightType::Point:
                        pointLightUi(*lights[i]);
                        break;
                    case LightType::Directional:
                        directionalLightUi(*lights[i]);
                        break;
                    }
                    
                    ImGui::EndTabItem();
                }
                i++;
            }
            ImGui::EndTabBar();
        }
    }
}


static void AddLightsWidget(LightManager& lightManager)
{
    if (ImGui::TreeNode("Lights"))
    {
        std::string items[] = { getLightTypeName(LightType::Spot), getLightTypeName(LightType::Point), getLightTypeName(LightType::Directional) };
        static int item_current_idx = 0; // Here we store our selection data as an index.
        if (ImGui::BeginListBox("lights"))
        {
            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                const bool is_selected = (item_current_idx == n);
                if (ImGui::Selectable(items[n].c_str(), is_selected))
                {
                    item_current_idx = n;
                    LightType type = getLightTypeByName(items[n]);
                    lightManager.addLight(type);
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
        ImGui::TreePop();
    }
}