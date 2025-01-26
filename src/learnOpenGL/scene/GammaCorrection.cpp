#include "GammaCorrection.h"

scene::GammaCorrection::GammaCorrection()
{
	shader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\GammaCorrection.shader"));

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

    texture = std::make_shared<Texture>(GetResourcePath("res\\textures\\wood.png"), TextureType::Diffuse, false);
    textureGammaCorrected = std::make_shared<Texture>(GetResourcePath("res\\textures\\wood.png"), TextureType::Diffuse, true);

    texture->Bind();
    shader->Bind();
    shader->SetUniform1i("floorTexture", 0);


    planeVAO->Unbind();
    planeVBO->Unbind();
    planeIBO->Unbind();
    shader->Unbind();
    texture->Unbind();
    textureGammaCorrected->Unbind();
}

scene::GammaCorrection::~GammaCorrection()
{
    planeVAO->Unbind();
    planeVBO->Unbind();
    planeIBO->Unbind();
    shader->Unbind();
    textureGammaCorrected->Unbind();
    texture->Unbind();
}

void scene::GammaCorrection::OnUpdate(float deltaTime)
{
    cameraController.OnUpdate(deltaTime);
}

void scene::GammaCorrection::OnMouseMovedEvent(double posX, double posY)
{
    cameraController.RotateCamera(posX, posY);
}

void scene::GammaCorrection::OnMouseScrolledEvent(double offsetX, double offsetY)
{
    cameraController.ZoomCamera(offsetX, offsetY);
}

void scene::GammaCorrection::OnRender()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cameraController.SetCameraSpeed(1);
    cameraController.SetCameraSensitvity(0.005);
    // draw objects
    shader->Bind();
    glm::mat4 projection = glm::perspective(glm::radians(cameraController.GetCamera().Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = cameraController.GetViewMatrix();
    shader->SetUniformMat4f("projection", projection);
    shader->SetUniformMat4f("view", view);

    shader->SetUniform3f("viewPos", cameraController.GetCameraPos());

    shader->SetUniform3fv("lightPositions", 4, &lightPositions[0][0]);
    shader->SetUniform3fv("lightColors", 4, &lightColors[0][0]);
    shader->Bind();
 
    shader->SetUniform1i("gamma", gammaEnabled);

    // floor
    planeVAO->Bind();
    if (gammaEnabled) {
        textureGammaCorrected->Bind();
    }
    else {
        texture->Bind();
    }
     
    renderer.Draw(*planeVAO, *planeIBO, *shader);
}

void scene::GammaCorrection::OnImGuiRender()
{
    ImGui::Checkbox("Gamma", &gammaEnabled);
}

void scene::GammaCorrection::OnEvent(int event)
{
    cameraController.ProcessInput(event);
}
