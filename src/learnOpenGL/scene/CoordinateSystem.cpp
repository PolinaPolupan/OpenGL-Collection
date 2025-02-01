#include "CoordinateSystem.h"

scene::CoordinateSystem::CoordinateSystem()
{
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2, 3, 4, 5,
        6, 7, 8, 9, 10, 11, 
        12, 13, 14, 15, 16, 17,
        18, 19, 20, 21, 22, 23, 
        24, 25, 26, 27, 28, 29,
        30, 31, 32, 33, 34, 35
    };
    m_FOV = 45.f;
    m_FarClipRange = 100.f;
    m_NearClipRange = 0.1f;
    m_CameraSpeed = 2.5f;
    m_Shader = std::make_unique<Shader>(GetResourcePath("res/shaders/CoordinateSystem.shader"));
    m_VAO = std::make_unique<VertexArray>();
    m_Texture = std::make_unique<Texture>(GetResourcePath("res/textures/container.jpg"), Texture::Type::Diffuse);
    Camera camera(
        glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        m_CameraSpeed
    );
  
    m_cameraController = CameraController(camera);

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    m_VAO->AddBuffer(*m_VBO, layout);
    m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 36);

    m_Shader->Bind();
    m_Texture->Bind();

    m_Shader->SetUniform1i("u_Texture", 0);

    m_VAO->Unbind();
    m_VBO->Unbind();
    m_IndexBuffer->Unbind();
    m_Shader->Unbind();
}

scene::CoordinateSystem::~CoordinateSystem()
{
    m_Shader->Unbind();
    m_Texture->Unbind();

    m_VAO->Unbind();
    m_VBO->Unbind();
    m_IndexBuffer->Unbind();
}

void scene::CoordinateSystem::OnUpdate(float deltaTime)
{
    m_cameraController.OnUpdate(deltaTime);
}

void scene::CoordinateSystem::OnMouseMovedEvent(double posX, double posY)
{
    m_cameraController.RotateCamera(posX, posY);
}

void scene::CoordinateSystem::OnMouseScrolledEvent(double offsetX, double offsetY)
{
    m_cameraController.ZoomCamera(offsetX, offsetY);
}

void scene::CoordinateSystem::OnRender()
{
    GLCall(glClearColor(0.f, 0.f, 0.f, 1.f));
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Renderer renderer;

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    m_VAO->Bind();
    m_Shader->Bind();
    m_cameraController.SetCameraSpeed(m_CameraSpeed);
    m_cameraController.SetCameraFOV(m_FOV);
   
    glm::mat4 projection = glm::perspective(glm::radians(m_cameraController.GetFOV()), 800.0f / 600.0f, m_NearClipRange, m_FarClipRange);
    m_Shader->SetUniformMat4f("view", m_cameraController.GetViewMatrix());
    m_Shader->SetUniformMat4f("projection", projection);

    for (unsigned int i = 0; i < 10; i++) {
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f);

        glm::vec3 pos = glm::vec3(cubePositions[i].x, cubePositions[i].y + sin((float)glfwGetTime()), cubePositions[i].z);
        model = glm::translate(model, pos);
        float angle = 20.0f * i;
        if (i % 3 == 0)
        {
            angle = 20.0f * glfwGetTime();
        }
        
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("model", model);
        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }
}

void scene::CoordinateSystem::OnImGuiRender()
{
    ImGui::SliderFloat("FOV", &m_FOV, 0.0f, 180.f);
    ImGui::SliderFloat("Near Clip Range", &m_NearClipRange, 0.1f, 180.f);
    ImGui::SliderFloat("Far Clip Range", &m_FarClipRange, 0.1f, 180.f);
    ImGui::SliderFloat("Camera speed", &m_CameraSpeed, 0.1f, 180.f);
}

void scene::CoordinateSystem::OnEvent(int event)
{
    m_cameraController.ProcessInput(event);
}
