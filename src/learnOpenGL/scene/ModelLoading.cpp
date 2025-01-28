#include "ModelLoading.h"

scene::ModelLoading::ModelLoading()
    : shader(GetResourcePath("res\\shaders\\StandardSurface.shader")), 
    selection(GetResourcePath("res\\shaders\\Light.shader"))
{
    m_ModelsPaths = GetObjectsPath();
}

scene::ModelLoading::~ModelLoading()
{
    shader.Unbind();
    selection.Unbind();
}

void scene::ModelLoading::OnUpdate(float deltaTime)
{
    cameraController.OnUpdate(deltaTime);
    lightManager.Update();
    objectManager.Update();
}

void scene::ModelLoading::OnMouseMovedEvent(double posX, double posY)
{
    cameraController.RotateCamera(posX, posY);
}

void scene::ModelLoading::OnMouseScrolledEvent(double offsetX, double offsetY)
{
    cameraController.ZoomCamera(offsetX, offsetY);
}

void scene::ModelLoading::OnEvent(int event)
{
    cameraController.ProcessInput(event);
}

void scene::ModelLoading::OnRender()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer.Submit(cameraController.GetCamera());
    shader.Bind();
    shader.SetUniform3f("viewPos", cameraController.GetCameraPos());
    shader.SetUniform1i("lightsNum", lightManager.GetLights().size());
    
    for (int i = 0; i < lightManager.GetLights().size(); i++)
    {
        renderer.RenderLight(*lightManager.GetLights()[i], shader);  
    }

    for (auto& o : objectManager.GetObjects())
    {
        renderer.RenderObject(*o, shader);
    }
    
}

void scene::ModelLoading::OnImGuiRender()
{
    if (ImGui::TreeNode("Load objects"))
    {
        static int item_current_idx = 0; // Here we store our selection data as an index.
        if (ImGui::BeginListBox("Models"))
        {
            for (int n = 0; n < m_ModelsPaths.size(); n++)
            {
                const bool is_selected = (item_current_idx == n);
                auto pos = m_ModelsPaths[n].find_last_of("\\");
          
                if (ImGui::Selectable(m_ModelsPaths[n].c_str(), is_selected))
                {
                    item_current_idx = n;
                    objectManager.AddObject(m_ModelsPaths[n]);
                }
                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
        
        ImGui::TreePop();
    }

    AddLightsWidget(lightManager);
  
    LightsTabBar(lightManager.GetLights());

    ObjectsList(objectManager);
}


