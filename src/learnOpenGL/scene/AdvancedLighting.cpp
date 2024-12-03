#include "AdvancedLighting.h"

scene::AdvancedLighting::AdvancedLighting()
{
    mode = Mode::BLIN_PHONG;

	shader = std::make_shared<Shader>(GetResourcePath("res/shaders/AdvancedLighting.shader"));
    
    float planeVertices[] = {
        // positions            // normals         // texcoords
         10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

         10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
         10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
    };

    unsigned int planeIndices[] = { 0, 1, 2, 3, 4, 5 };

    planeVAO = std::make_shared<VertexArray>();
    planeVBO = std::make_shared<VertexBuffer>(planeVertices, sizeof(planeVertices));
    planeIBO = std::make_shared<IndexBuffer>(planeIndices, sizeof(planeIndices));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);

    planeVAO->AddBuffer(*planeVBO, layout);

    texture = std::make_shared<Texture>(GetResourcePath("res/textures/wood.png"));

    texture->Bind();
    shader->Bind();
    shader->SetUniform1i("floorTexture", 0);

    planeVAO->Unbind();
    planeVBO->Unbind();
    planeIBO->Unbind();
    shader->Unbind();
    texture->Unbind();
}

scene::AdvancedLighting::~AdvancedLighting()
{
    planeVAO->Unbind();
    planeVBO->Unbind();
    planeIBO->Unbind();
    shader->Unbind();
    texture->Unbind();
}

void scene::AdvancedLighting::OnUpdate(float deltaTime)
{
    cameraController.OnUpdate(deltaTime);
}

void scene::AdvancedLighting::OnMouseMovedEvent(double posX, double posY)
{
    cameraController.rotateCamera(posX, posY);
}

void scene::AdvancedLighting::OnMouseScrolledEvent(double offsetX, double offsetY)
{
    cameraController.zoomCamera(offsetX, offsetY);
}

void scene::AdvancedLighting::OnRender()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cameraController.setCameraSpeed(1);
    // draw objects
    shader->Bind();
    glm::mat4 projection = glm::perspective(glm::radians(cameraController.getCamera().Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = cameraController.getViewMatrix();
    shader->SetUniformMat4f("projection", projection);
    shader->SetUniformMat4f("view", view);
    // set light uniforms
    shader->SetUniform3f("viewPos", cameraController.getCameraPos());
    shader->SetUniform3f("lightPos", lightPos);

    if (mode == Mode::BLIN_PHONG) {
        shader->SetUniform1i("blinn", 1);
    }
    else {
        shader->SetUniform1i("blinn", 0);
    }
    
    // floor
    planeVAO->Bind();
    texture->Bind();
    renderer.Draw(*planeVAO, *planeIBO, *shader);
}

void scene::AdvancedLighting::OnImGuiRender()
{
    if (ImGui::Button("Phong")) {
        mode = Mode::PHONG;
    }
    if (ImGui::Button("Blin-Phong")) {
        mode = Mode::BLIN_PHONG;
    }
    ImGui::SliderFloat3("Light pos", &lightPos[0], -5, 5);
}

void scene::AdvancedLighting::OnEvent(int event)
{
    cameraController.processInput(event);
}
