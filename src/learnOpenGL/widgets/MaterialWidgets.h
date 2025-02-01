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

static void materialMapBrowser(std::vector<std::shared_ptr<Texture>>& textures, Material& material, Texture::Type& TextureType)
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
        if (ImGui::ImageButton(textures[i]->GetPath().c_str(), (void*)textures[i]->GetId(), ImVec2(50, 50)))
        {
            switch (TextureType)
            {
            case Texture::Type::Diffuse:
                material.SetDiffuseMap(textures[i]->GetPath());

                std::cout << "Diffuse map " << textures[i]->GetPath() << " set" << "\n";
                break;
            case Texture::Type::Specular:
                material.SetSpecularMap(textures[i]->GetPath());

                std::cout << "Specular map " << textures[i]->GetPath() << " set" << "\n";
                break;
            case Texture::Type::Emission:
                material.SetEmissionMap(textures[i]->GetPath());

                std::cout << "Emission map " << textures[i]->GetPath() << " set" << "\n";
                break;
            default:
                break;
            }
        }
    }
}

static void diffuseUi(Material& material, bool& showMaterialBrowser, Texture::Type& TextureType)
{
    ImGui::Text("Diffuse");
    if (ImGui::Button("Set diffuse map"))
    {
        TextureType = Texture::Type::Diffuse;
        showMaterialBrowser = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset diffuse map"))
    {
        material.SetDiffuseMap(GetResourcePath("white.jpg"));
    }
    ImGui::ColorEdit3("Diffuse color", &material.diffuseColor[0]);
}

static void specularUi(Material& material, bool& showMaterialBrowser, Texture::Type& TextureType)
{
    ImGui::Text("Specular");
    if (ImGui::Button("Set specular map"))
    {
        TextureType = Texture::Type::Specular;
        showMaterialBrowser = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset specular map"))
    {
        material.SetSpecularMap(GetResourcePath("white.jpg"));
    }
    ImGui::ColorEdit3("Specular color", &material.specularColor[0]);
    ImGui::SliderFloat("Shininess", &material.shininess, 1.f, 256.f);
}

static void emissionUi(Material& material, bool& showMaterialBrowser, Texture::Type& TextureType)
{
    ImGui::Text("Emission");
    if (ImGui::Button("Set emission map"))
    {
        TextureType = Texture::Type::Emission;
        showMaterialBrowser = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset emission map"))
    {
        material.SetEmissionMap(GetResourcePath("white.jpg"));
    }
    ImGui::SliderFloat("Emission", &material.emissionWeight, 0.f, 1.f);
}
