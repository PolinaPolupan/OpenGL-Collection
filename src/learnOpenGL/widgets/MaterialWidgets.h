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
#include "FileUtils.h"

static void materialMapBrowser(std::vector<std::unique_ptr<Texture>>& textures, Material& material, TextureType& TextureType)
{
    for (int i = 0; i < textures.size(); i++)
    {
        if (i % 3 == 0)
        {
            ImGui::NewLine();
        }
        else
        {
            ImGui::SameLine();
        }
        if (ImGui::ImageButton(textures[i]->getPath().c_str(), (void*)textures[i]->GetId(), ImVec2(50, 50)))
        {
            switch (TextureType)
            {
            case Diffuse:
                material.setDiffuseMap(textures[i]->getPath());

                std::cout << "Diffuse map " << textures[i]->getPath() << " set" << "\n";
                break;
            case Specular:
                material.setSpecularMap(textures[i]->getPath());

                std::cout << "Specular map " << textures[i]->getPath() << " set" << "\n";
                break;
            case Emission:
                material.setEmissionMap(textures[i]->getPath());

                std::cout << "Emission map " << textures[i]->getPath() << " set" << "\n";
                break;
            default:
                break;
            }
        }
    }
}

static void diffuseUi(Material& material, bool& showMaterialBrowser, TextureType& TextureType)
{
    ImGui::Text("Diffuse");
    if (ImGui::Button("Set diffuse map"))
    {
        TextureType = TextureType::Diffuse;
        showMaterialBrowser = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset diffuse map"))
    {
        material.setDiffuseMap(GetResourcePath("white.jpg"));
    }
    ImGui::ColorEdit3("Diffuse color", &material.diffuseColor[0]);
}

static void specularUi(Material& material, bool& showMaterialBrowser, TextureType& TextureType)
{
    ImGui::Text("Specular");
    if (ImGui::Button("Set specular map"))
    {
        TextureType = TextureType::Specular;
        showMaterialBrowser = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset specular map"))
    {
        material.setSpecularMap(GetResourcePath("white.jpg"));
    }
    ImGui::ColorEdit3("Specular color", &material.specularColor[0]);
    ImGui::SliderFloat("Shininess", &material.shininess, 1.f, 256.f);
}

static void emissionUi(Material& material, bool& showMaterialBrowser, TextureType& TextureType)
{
    ImGui::Text("Emission");
    if (ImGui::Button("Set emission map"))
    {
        TextureType = TextureType::Emission;
        showMaterialBrowser = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset emission map"))
    {
        material.setEmissionMap(GetResourcePath("white.jpg"));
    }
    ImGui::SliderFloat("Emission", &material.emissionWeight, 0.f, 1.f);
}
