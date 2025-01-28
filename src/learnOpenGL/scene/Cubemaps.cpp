#include "Cubemaps.h"

scene::Cubemaps::Cubemaps():
    shader(GetResourcePath("res/shaders/Cubemaps.shader")),
    skyboxShader(GetResourcePath("res/shaders/Skybox.shader")),
    cubeTexture(GetResourcePath("res/textures/wall.jpg"), TextureType::Diffuse)
{
    float skyboxVertices[] = { 
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    float cubeVertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    unsigned int cubeIndices[] = {
        0, 1, 2, 3, 4, 5,
        6, 7, 8, 9, 10, 11,
        12, 13, 14, 15, 16, 17,
        18, 19, 20, 21, 22, 23,
        24, 25, 26, 27, 28, 29,
        30, 31, 32, 33, 34, 35
    };

    cubeVBO = std::make_shared<VertexBuffer>(cubeVertices, sizeof(cubeVertices));
    cubeIBO = std::make_shared<IndexBuffer>(cubeIndices, 36);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    cubeVAO.AddBuffer(*cubeVBO, layout);

    skyboxVBO = std::make_shared<VertexBuffer>(skyboxVertices, sizeof(skyboxVertices));
    skyboxIBO = std::make_shared<IndexBuffer>(cubeIndices, 36);
    VertexBufferLayout layout1;
    layout1.Push<float>(3);
    skyboxVAO.AddBuffer(*skyboxVBO, layout1);

    std::vector<std::string> faces
    {
        GetResourcePath("res\\textures\\skybox\\right.jpg").string(),
        GetResourcePath("res\\textures\\skybox\\left.jpg").string(),
        GetResourcePath("res\\textures\\skybox\\top.jpg").string(),
        GetResourcePath("res\\textures\\skybox\\bottom.jpg").string(),
        GetResourcePath("res\\textures\\skybox\\front.jpg").string(),
        GetResourcePath("res\\textures\\skybox\\back.jpg").string()
    };

    cubemapTexture = LoadCubemap(faces);

    // shader configuration
    // --------------------
    shader.Bind();
    shader.SetUniform1i("texture1", 0);

    skyboxShader.Bind();
    skyboxShader.SetUniform1i("skybox", 0);

    modelsPaths = GetObjectsPath();
}

scene::Cubemaps::~Cubemaps()
{
}

void scene::Cubemaps::OnUpdate(float deltaTime)
{
    cameraController.OnUpdate(deltaTime);
    objectManager.Update();
}

void scene::Cubemaps::OnMouseMovedEvent(double posX, double posY)
{
    cameraController.RotateCamera(posX, posY);
}

void scene::Cubemaps::OnMouseScrolledEvent(double offsetX, double offsetY)
{
    cameraController.ZoomCamera(offsetX, offsetY);
}

void scene::Cubemaps::OnRender()
{
    // render
        // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer.Submit(cameraController.GetCamera());

    // draw scene as normal
    shader.Bind();
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = cameraController.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    shader.SetUniformMat4f("model", model);
    shader.SetUniformMat4f("view", view);
    shader.SetUniformMat4f("projection", projection);
    shader.SetUniform3f("cameraPos", cameraController.GetCameraPos());

    // cubes
    cubeVAO.Bind();
    cubeTexture.Bind();
    renderer.Draw(cubeVAO, *cubeIBO, shader);

    for (auto& o : objectManager.GetObjects())
    {
        shader.Bind();
        renderer.RenderObject(*o, shader);
    }


    // draw skybox as last
    glDepthFunc(GL_LEQUAL);  // change depth function so depth scene passes when values are equal to depth buffer's content
    skyboxShader.Bind();
    view = glm::mat4(glm::mat3(cameraController.GetViewMatrix())); // remove translation from the view matrix
    skyboxShader.SetUniformMat4f("view", view);
    skyboxShader.SetUniformMat4f("projection", projection);
    // skybox cube
    skyboxVAO.Bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    renderer.Draw(skyboxVAO, *skyboxIBO, skyboxShader);
    glDepthFunc(GL_LESS); // set depth function back to default

}

void scene::Cubemaps::OnImGuiRender()
{
    LoadObjectsList(modelsPaths, objectManager);
}

void scene::Cubemaps::OnEvent(int event)
{
    cameraController.ProcessInput(event);
}
