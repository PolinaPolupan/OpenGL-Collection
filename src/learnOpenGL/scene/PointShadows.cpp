#include "PointShadows.h"

scene::PointShadows::PointShadows()
{
    shader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\PointShadows.shader"));
    simpleDepthShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\PointShadowsDepth.shader"));
    debugDepthQuad = std::make_shared<Shader>(GetResourcePath("res\\shaders\\DebugQuadDepth.shader"));


    float planeVertices[] = {
        // positions            // normals         // texcoords
         25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
        -25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

         25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
        -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
         25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
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

    float cubeVertices[] = {
        // back face
        -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
         1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
         1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
         1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
        -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
        -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
        // front face
        -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
         1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
         1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
         1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
        -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
        -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
        // left face
        -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
        -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
        -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
        -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
        -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
        -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
        // right face
         1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
         1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
         1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
         1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
         1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
         1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
        // bottom face
        -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
         1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
         1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
         1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
        -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
        -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
        // top face
        -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
         1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
         1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
         1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
        -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
        -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
    };


    unsigned int cubeIndices[] = {
        0, 1, 2, 3, 4, 5,
        6, 7, 8, 9, 10, 11,
        12, 13, 14, 15, 16, 17,
        18, 19, 20, 21, 22, 23,
        24, 25, 26, 27, 28, 29,
        30, 31, 32, 33, 34, 35
    };


    cubeVAO = std::make_shared<VertexArray>();
    cubeVBO = std::make_shared<VertexBuffer>(cubeVertices, sizeof(cubeVertices));
    cubeIBO = std::make_shared<IndexBuffer>(cubeIndices, sizeof(cubeIndices));

    VertexBufferLayout layout1;
    layout1.Push<float>(3);
    layout1.Push<float>(3);
    layout1.Push<float>(2);

    cubeVAO->AddBuffer(*cubeVBO, layout1);


    float quadVertices[] = {
        // positions        // texture Coords
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };

    quadVAO = std::make_shared<VertexArray>();
    quadVBO = std::make_shared<VertexBuffer>(quadVertices, sizeof(quadVertices));

    VertexBufferLayout layout2;
    layout2.Push<float>(3);
    layout2.Push<float>(2);

    quadVAO->AddBuffer(*quadVBO, layout2);


    texture = std::make_shared<Texture>(GetResourcePath("res\\textures\\wood.png"));

    // configure depth map FBO
    // -----------------------
    glGenFramebuffers(1, &depthMapFBO);
    // create depth cubemap texture
    glGenTextures(1, &depthCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
    for (unsigned int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    texture->Bind();
    shader->Bind();
    shader->SetUniform1i("diffuseTexture", 0);
    shader->SetUniform1i("depthMap", 1);

    debugDepthQuad->Bind();
    debugDepthQuad->SetUniform1i("depthMap", 0);

    planeVAO->Unbind();
    planeVBO->Unbind();
    planeIBO->Unbind();
    shader->Unbind();
    texture->Unbind();
    cubeVAO->Unbind();
    cubeVBO->Unbind();
    cubeIBO->Unbind();
    simpleDepthShader->Unbind();
    debugDepthQuad->Unbind();
}

scene::PointShadows::~PointShadows()
{
    planeVAO->Unbind();
    planeVBO->Unbind();
    planeIBO->Unbind();
    shader->Unbind();
    texture->Unbind();
    cubeVAO->Unbind();
    cubeVBO->Unbind();
    cubeIBO->Unbind();
    simpleDepthShader->Unbind();
    debugDepthQuad->Unbind();
}

void scene::PointShadows::OnUpdate(float deltaTime)
{
    cameraController.OnUpdate(deltaTime);
}

void scene::PointShadows::OnMouseMovedEvent(double posX, double posY)
{
    cameraController.RotateCamera(posX, posY);
}

void scene::PointShadows::OnMouseScrolledEvent(double offsetX, double offsetY)
{
    cameraController.ZoomCamera(offsetX, offsetY);
}

void scene::PointShadows::OnRender()
{
    // move light position over time
    lightPos.z = static_cast<float>(sin(glfwGetTime() * 0.5) * 3.0);

    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 0. create depth cubemap transformation matrices
    // -----------------------------------------------
    float near_plane = 1.0f;
    float far_plane = 25.0f;
    glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
    std::vector<glm::mat4> shadowTransforms;
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

    // 1. render scene to depth cubemap
    // --------------------------------
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    simpleDepthShader->Bind();
    for (unsigned int i = 0; i < 6; ++i)
        simpleDepthShader->SetUniformMat4f("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
    simpleDepthShader->SetUniform1f("far_plane", far_plane);
    simpleDepthShader->SetUniform3f("lightPos", lightPos);
    RenderScene(simpleDepthShader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 2. render scene as normal 
    // -------------------------
    glViewport(0, 0, WIDTH, HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->Bind();
    glm::mat4 projection = glm::perspective(glm::radians(cameraController.GetCamera().Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = cameraController.GetViewMatrix();
    shader->SetUniformMat4f("projection", projection);
    shader->SetUniformMat4f("view", view);
    // set lighting uniforms
    shader->SetUniform3f("lightPos", lightPos);
    shader->SetUniform3f("viewPos", cameraController.GetCameraPos());
    shader->SetUniform1i("shadows", shadows); // enable/disable shadows by pressing 'SPACE'
    shader->SetUniform1f("far_plane", far_plane);
    texture->Bind();
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
    RenderScene(shader);
}

void scene::PointShadows::OnImGuiRender()
{
}

void scene::PointShadows::OnEvent(int event)
{
    cameraController.ProcessInput(event);
}

void scene::PointShadows::RenderScene(std::shared_ptr<Shader> shader)
{
    cameraController.SetCameraSpeed(1);
    // draw objects
    shader->Bind();

    glm::mat4 model = glm::mat4(1.0f);
    shader->SetUniformMat4f("model", model);

    // floor
    renderer.Draw(*planeVAO, *planeIBO, *shader);
    // cubes
    shader->Bind();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
    model = glm::scale(model, glm::vec3(0.5f));
    shader->SetUniformMat4f("model", model);
    renderer.Draw(*cubeVAO, *cubeIBO, *shader);

    shader->Bind();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
    model = glm::scale(model, glm::vec3(0.5f));
    shader->SetUniformMat4f("model", model);
    renderer.Draw(*cubeVAO, *cubeIBO, *shader);

    shader->Bind();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
    model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    model = glm::scale(model, glm::vec3(0.25));
    shader->SetUniformMat4f("model", model);
    renderer.Draw(*cubeVAO, *cubeIBO, *shader);
}

void scene::PointShadows::RenderQuad()
{
}
