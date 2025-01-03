#include "BasicLighting.h"

scene::BasicLighting::BasicLighting()
{
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2, 3, 4, 5,
        6, 7, 8, 9, 10, 11,
        12, 13, 14, 15, 16, 17,
        18, 19, 20, 21, 22, 23,
        24, 25, 26, 27, 28, 29,
        30, 31, 32, 33, 34, 35
    };

    m_CameraSpeed = 2.5f;

    material.setDiffuseMap(GetResourcePath("res/textures/container2.png"));
    material.setSpecularMap(GetResourcePath("res/textures/container2_specular.png"));
    material.setEmissionMap(GetResourcePath("res/textures/matrix.jpg"));

    textures = getTextures();
 
    m_Shader = std::make_unique<Shader>(GetResourcePath("res/shaders/BasicSpotlight.shader"));
    m_VAO = std::make_unique<VertexArray>();
    m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 36);
    m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));

   VertexBufferLayout layout;

    Camera camera(
        glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        m_CameraSpeed
    );
    m_cameraController = CameraController(camera);

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
  
    m_VAO->AddBuffer(*m_VBO, layout);

    material.diffuseMap->Bind();
    material.specularMap->Bind(1);
    material.emissionMap->Bind(2);
    m_IndexBuffer->Bind();
    m_Shader->Bind();

    m_VAO->Unbind();
    m_VBO->Unbind();
    m_IndexBuffer->Unbind();
    m_Shader->Unbind();
   
}

scene::BasicLighting::~BasicLighting()
{
    material.diffuseMap->Unbind();
    material.specularMap->Unbind();
    material.emissionMap->Unbind();
    m_IndexBuffer->Unbind();
    m_Shader->Unbind();

    m_VAO->Unbind();
    m_VBO->Unbind();
    m_IndexBuffer->Unbind();
    m_Shader->Unbind();
}

void scene::BasicLighting::OnUpdate(float deltaTime)
{
    m_cameraController.OnUpdate(deltaTime);
    lightManager.update();
}

void scene::BasicLighting::OnRender()
{
     GLCall(glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.f));
     glEnable(GL_DEPTH_TEST);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     Renderer renderer;
     renderer.Submit(m_cameraController.getCamera());
     {
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("view", m_cameraController.getViewMatrix());
        m_Shader->SetUniformMat4f("projection", m_cameraController.getProjectionMatrix());
        m_Shader->SetUniformMat4f("model", glm::mat4(1.f));
        
        m_Shader->SetUniform3f("viewPos", m_cameraController.getCameraPos());
 
        m_Shader->SetUniform1i("lightsNum", lightManager.getLights().size());
        m_Shader->SetUniform3f("material.diffuseColor", material.diffuseColor);
        m_Shader->SetUniform3f("material.specularColor", material.specularColor);
        material.diffuseMap->Bind(0);
        m_Shader->SetUniform1i("material.diffuse", 0);
        material.specularMap->Bind(1);
        m_Shader->SetUniform1i("material.specular", 1);
        material.emissionMap->Bind(2);
        m_Shader->Bind();
        m_Shader->SetUniform1i("material.emission", 2);
        m_Shader->SetUniform1f("material.shininess", material.shininess);
        m_Shader->SetUniform1f("material.emissionWeight", material.emissionWeight);

        for (int i = 0; i < lightManager.getLights().size(); i++)
        {
            m_Shader->Bind();
            renderer.RenderLight(*lightManager.getLights()[i], *m_Shader);
        }
        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

}

bool show_edit = false;
LightType lightType = LightType::Default;
TextureType textureType = TextureType::Diffuse;

void scene::BasicLighting::OnImGuiRender()
{
    ImGui::ColorEdit3("Background Color", &backgroundColor[0]);
    diffuseUi(material, show_edit, textureType);
    specularUi(material, show_edit, textureType);
    emissionUi(material, show_edit, textureType);

    AddLightsWidget(lightManager);

    LightsTabBar(lightManager.getLights());
    
    if (show_edit)
    {
        ImGui::Begin("Textures", &show_edit, ImGuiWindowFlags_MenuBar);    
        materialMapBrowser(textures, material, textureType);
        ImGui::End();
    }
}

void scene::BasicLighting::OnEvent(int event)
{
    m_cameraController.processInput(event);
}

void scene::BasicLighting::OnMouseMovedEvent(double posX, double posY)
{
    m_cameraController.rotateCamera(posX, posY);
}
