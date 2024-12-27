#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <memory>
#include "Constants.h"
#include "Texture.h"
#include "Material.h"
#include "imgui.h"
#include "ObjectManager.h"


static void objectUi(Model& object)
{
    ImGui::SliderFloat3("Position", &object.position[0], -20.f, 20.f);
    ImGui::SliderFloat3("Scale", &object.scale[0], -20.f, 20.f);
}

static void ObjectsList(ObjectManager& objectManager)
{
    static int item_current_idx = 0; // Here we store our selection data as an index.
    if (ImGui::TreeNode("Objects"))
    {  
        if (ImGui::BeginListBox("objects"))
        {
            std::vector<std::string> items;
            for (auto& o : objectManager.getObjects())
            {
                items.push_back(o->name);
            }
            for (int n = 0; n < objectManager.getObjects().size(); n++)
            {
                const bool is_selected = (item_current_idx == n);
                if (ImGui::Selectable((items[n] + std::to_string(n)).c_str(), is_selected))
                {
                    item_current_idx = n;
                    
                }
                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                    objectManager.getObjects()[objectManager.current_selected_object]->isSelected = false;
                    objectManager.current_selected_object = n;
                    objectManager.getObjects()[objectManager.current_selected_object]->isSelected = true;
                }
                    
            }
            ImGui::EndListBox();
        }
        ImGui::TreePop();
    }
    if (objectManager.getObjects().size())
    {
        objectUi(*objectManager.getObjects()[objectManager.current_selected_object]);
    }
}

static void LoadObjectsList(std::vector<std::string>& modelsPaths, ObjectManager& objectManager) {

    if (ImGui::TreeNode("Load objects"))
    {
        static int item_current_idx = 0; // Here we store our selection data as an index.
        if (ImGui::BeginListBox("Models"))
        {
            for (int n = 0; n < modelsPaths.size(); n++)
            {
                const bool is_selected = (item_current_idx == n);
                auto pos = modelsPaths[n].find_last_of("\\");

                std::string name = std::filesystem::path(modelsPaths[n]).filename().string();

                if (ImGui::Selectable(name.c_str(), is_selected))
                {
                    item_current_idx = n;
                    objectManager.addObject(modelsPaths[n]);
                }
                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }

        ImGui::TreePop();
    }

    ObjectsList(objectManager);
}