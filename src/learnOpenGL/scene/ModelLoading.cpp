#include "ModelLoading.h"

scene::ModelLoading::ModelLoading()
    : shader(GetResourcePath("res\\shaders\\StandardSurface.shader")), 
    selection(GetResourcePath("res\\shaders\\Light.shader"))
{
    m_ModelsPaths = getObjectsPath();
}

scene::ModelLoading::~ModelLoading()
{
    shader.Unbind();
    selection.Unbind();
}

void scene::ModelLoading::OnUpdate(float deltaTime)
{
    cameraController.OnUpdate(deltaTime);
    lightManager.update();
    objectManager.update();
}

void scene::ModelLoading::OnMouseMovedEvent(double posX, double posY)
{
    cameraController.rotateCamera(posX, posY);
}

void scene::ModelLoading::OnMouseScrolledEvent(double offsetX, double offsetY)
{
    cameraController.zoomCamera(offsetX, offsetY);
}

void scene::ModelLoading::OnEvent(int event)
{
    cameraController.processInput(event);
}

void scene::ModelLoading::OnRender()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer.Submit(cameraController.getCamera());
    shader.Bind();
    shader.SetUniform3f("viewPos", cameraController.getCameraPos());
    shader.SetUniform1i("lightsNum", lightManager.getLights().size());
    
    for (int i = 0; i < lightManager.getLights().size(); i++)
    {
        renderer.RenderLight(*lightManager.getLights()[i], shader);  
    }

    for (auto& o : objectManager.getObjects())
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
                    objectManager.addObject(m_ModelsPaths[n]);
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
  
    LightsTabBar(lightManager.getLights());

    ObjectsList(objectManager);
}


