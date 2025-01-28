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


static void ObjectUi(Model& object)
{
    ImGui::SliderFloat3("Position", &object.position[0], -20.f, 20.f);
    if (ImGui::SliderFloat("Scale1", &object.scale[0], 0, 1)) {
        object.scale[1] = object.scale[2] = object.scale[0];
    }
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
            for (auto& o : objectManager.GetObjects())
            {
                items.push_back(o->name);
            }
            for (int n = 0; n < objectManager.GetObjects().size(); n++)
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
                    objectManager.GetObjects()[objectManager.current_selected_object]->isSelected = false;
                    objectManager.current_selected_object = n;
                    objectManager.GetObjects()[objectManager.current_selected_object]->isSelected = true;

                    // Context menu
                    if (ImGui::BeginPopupContextWindow())
                    {
                        ImGui::Text(objectManager.GetObjects()[objectManager.current_selected_object]->name.c_str());
                        ImGui::Separator();
                        if (ImGui::MenuItem("Delete", "Del")) {
                            objectManager.DeleteObject(n);
                        }

                        ImGui::EndPopup();
                    }
                }
                    
            }
            ImGui::EndListBox();
        }
        ImGui::TreePop();
    }
    if (objectManager.GetObjects().size())
    {
        ObjectUi(*objectManager.GetObjects()[objectManager.current_selected_object]);
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
                    objectManager.AddObject(modelsPaths[n]);
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