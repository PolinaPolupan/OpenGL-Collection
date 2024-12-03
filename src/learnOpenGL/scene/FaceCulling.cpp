#include "FaceCulling.h"

scene::FaceCulling::FaceCulling() : 
    shader(GetResourcePath("res\\shaders\\FaceCulling.shader")),
    cubeTexture(GetResourcePath("res\\textures\\wall.jpg"), TextureType::Diffuse)
{
    float cubeVertices[] = {
        // positions          // texture Coords
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

    unsigned int cubeIndices[] = {
        0, 1, 2, 3, 4, 5,
        6, 7, 8, 9, 10, 11,
        12, 13, 14, 15, 16, 17,
        18, 19, 20, 21, 22, 23,
        24, 25, 26, 27, 28, 29,
        30, 31, 32, 33, 34, 35
    };

    float planeVertices[] = {
        // positions          // texture Coords 
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };

    unsigned int planeIndices[] = { 0, 1, 2, 3, 4, 5 };

    VertexBuffer cubeVBO = VertexBuffer(cubeVertices, sizeof(cubeVertices));
    cubeIBO = std::make_unique<IndexBuffer>(cubeIndices, 36);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    cubeVAO.AddBuffer(cubeVBO, layout);

    VertexBuffer planeVBO = VertexBuffer(planeVertices, sizeof(planeVertices));
    planeIBO = std::make_unique<IndexBuffer>(planeIndices, 6);
    planeVAO.AddBuffer(planeVBO, layout);

    cubeIBO->Bind();
    planeIBO->Bind();
    shader.Bind();
    cubeTexture.Bind();

    shader.SetUniform1i("texture1", 0);
}

scene::FaceCulling::~FaceCulling()
{
    cubeVAO.Unbind();
    cubeIBO->Unbind();
    cubeTexture.Unbind();

    planeVAO.Unbind();
    planeIBO->Unbind();

    shader.Unbind();

    glDisable(GL_CULL_FACE);
}

void scene::FaceCulling::OnUpdate(float deltaTime)
{
    cameraController.OnUpdate(deltaTime);
}

void scene::FaceCulling::OnMouseMovedEvent(double posX, double posY)
{
    cameraController.rotateCamera(posX, posY);
}

void scene::FaceCulling::OnMouseScrolledEvent(double offsetX, double offsetY)
{
    cameraController.zoomCamera(offsetX, offsetY);
}

void scene::FaceCulling::OnRender()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer.Submit(cameraController.getCamera());

    shader.Bind();
    glm::mat4 projection = glm::perspective(glm::radians(45.f), 800.0f / 600.0f, 0.1f, 100.f);
    shader.SetUniformMat4f("view", cameraController.getViewMatrix());
    shader.SetUniformMat4f("projection", projection);

    glm::mat4 model = glm::mat4(1.f);

    cubeVAO.Bind();
    cubeTexture.Bind();
    shader.SetUniformMat4f("model", model);
    renderer.Draw(cubeVAO, *cubeIBO, shader);

    planeVAO.Bind();
    cubeTexture.Bind();
    shader.Bind();
    shader.SetUniformMat4f("model", glm::mat4(1.f));
    renderer.Draw(planeVAO, *planeIBO, shader);
}

void scene::FaceCulling::OnImGuiRender()
{
    static bool enabledCulling = true;
    if (ImGui::Checkbox("Culling", &enabledCulling))
    {
        if (enabledCulling) glEnable(GL_CULL_FACE);
        else glDisable(GL_CULL_FACE);
    }
    if (ImGui::BeginListBox("Cull Face"))
    {
        static int front = true;
        ImGui::RadioButton("Gl Back", &front, 0);
        ImGui::RadioButton("Gl Front", &front, 1);
        if (front) glCullFace(GL_FRONT);
        else glCullFace(GL_BACK);
        ImGui::EndListBox();
    }
    if (ImGui::BeginListBox("Direction"))
    {
        static int clockwise = true;
 
        ImGui::RadioButton("Gl Back", &clockwise, 0);
        ImGui::RadioButton("Gl Front", &clockwise, 1);
        if (clockwise) glFrontFace(GL_CW);
        else glFrontFace(GL_CCW);
        ImGui::EndListBox();
    }
}

void scene::FaceCulling::OnEvent(int event)
{
    cameraController.processInput(event);
}
