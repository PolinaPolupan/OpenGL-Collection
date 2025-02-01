#include "Blending.h"

scene::Blending::Blending() : 
    cubeTexture(GetResourcePath("res/textures/wall.jpg"), Texture::Type::Diffuse),
    floorTexture(GetResourcePath("res/textures/wall.jpg"), Texture::Type::Diffuse),
    transparentTexture(GetResourcePath("res/textures/grass.png"), Texture::Type::Diffuse),
    windowTexture(GetResourcePath("res/textures/blending_transparent_window.png"), Texture::Type::Diffuse),
    shader(GetResourcePath("res/shaders/Blending.shader"))
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
    float transparentVertices[] = {
        // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
        1.0f,  0.5f,  0.0f,  1.0f,  0.0f
    };

    unsigned int planeIndices[] = { 0, 1, 2, 3, 4, 5 };
    unsigned int transparentIndices[] = { 0, 1, 2, 3, 4, 5 };

    VertexBuffer cubeVBO = VertexBuffer(cubeVertices, sizeof(cubeVertices));
    cubeIBO = std::make_unique<IndexBuffer>(cubeIndices, 36);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    cubeVAO.AddBuffer(cubeVBO, layout);

    VertexBuffer planeVBO = VertexBuffer(planeVertices, sizeof(planeVertices));
    planeIBO = std::make_unique<IndexBuffer>(planeIndices, 6);
    planeVAO.AddBuffer(planeVBO, layout);

    VertexBuffer transparentVBO = VertexBuffer(transparentVertices, sizeof(transparentVertices));
    transparentIBO = std::make_unique<IndexBuffer>(transparentIndices, 6);
    transparentVAO.AddBuffer(transparentVBO, layout);

    cubeIBO->Bind();
    planeIBO->Bind();
    transparentIBO->Bind();
    shader.Bind();
    cubeTexture.Bind();
    floorTexture.Bind();
    transparentTexture.Bind();

    shader.SetUniform1i("texture1", 0);
}

scene::Blending::~Blending()
{
    cubeVAO.Unbind();
    cubeIBO->Unbind();

    planeVAO.Unbind();
    planeIBO->Unbind();

    transparentVAO.Unbind();
    transparentIBO->Unbind();
    
    shader.Unbind();

    floorTexture.Unbind();
    transparentTexture.Unbind();
    windowTexture.Unbind();
    cubeTexture.Unbind();

    glDisable(GL_BLEND);
}

void scene::Blending::OnUpdate(float deltaTime)
{
	cameraController.OnUpdate(deltaTime);
}

void scene::Blending::OnMouseMovedEvent(double posX, double posY)
{
	cameraController.RotateCamera(posX, posY);
}

void scene::Blending::OnMouseScrolledEvent(double offsetX, double offsetY)
{
	cameraController.ZoomCamera(offsetX, offsetY);
}

std::vector<glm::vec3> vegetation
{
    glm::vec3(-1.5f, 0.0f, -0.48f),
    glm::vec3(1.5f, 0.0f, 0.51f),
    glm::vec3(0.0f, 0.0f, 0.7f),
    glm::vec3(-0.3f, 0.0f, -2.3f),
    glm::vec3(0.5f, 0.0f, -0.6f)
};

void scene::Blending::OnRender()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    renderer.Submit(cameraController.GetCamera());

    shader.Bind();
    glm::mat4 projection = glm::perspective(glm::radians(45.f), 800.0f / 600.0f, 0.1f, 100.f);
    shader.SetUniformMat4f("view", cameraController.GetViewMatrix());
    shader.SetUniformMat4f("projection", projection);

    glm::mat4 model = glm::mat4(1.f);

    cubeVAO.Bind();
    windowTexture.Bind();
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    shader.SetUniformMat4f("model", model);
    renderer.Draw(cubeVAO, *cubeIBO, shader);

    shader.Bind();
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    shader.SetUniformMat4f("model", model);
    renderer.Draw(cubeVAO, *cubeIBO, shader);
    
    planeVAO.Bind();
    floorTexture.Bind();
    shader.Bind();
    shader.SetUniformMat4f("model", glm::mat4(1.f));
    renderer.Draw(planeVAO, *planeIBO, shader);

    model = glm::mat4(1.0f);
    for (unsigned int i = 0; i < vegetation.size(); i++)
    {
        transparentVAO.Bind();
        transparentTexture.Bind();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, vegetation[i]);
        shader.Bind();
        shader.SetUniformMat4f("model", model);
        renderer.Draw(transparentVAO, *transparentIBO, shader);
    }
}

void scene::Blending::OnImGuiRender()
{
}

void scene::Blending::OnEvent(int event)
{
	cameraController.ProcessInput(event);
}
