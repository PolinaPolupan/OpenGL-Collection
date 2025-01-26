#include "ShadowMapping.h"

scene::ShadowMapping::ShadowMapping()
{
    shader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\ShadowMapping.shader"));
    simpleDepthShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\ShadowMappingDepth.shader"));
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

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    texture->Bind();
    shader->Bind();
    shader->SetUniform1i("diffuseTexture", 0);
    shader->SetUniform1i("shadowMap", 1);

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

scene::ShadowMapping::~ShadowMapping()
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

void scene::ShadowMapping::OnUpdate(float deltaTime)
{
    cameraController.OnUpdate(deltaTime);
}

void scene::ShadowMapping::OnMouseMovedEvent(double posX, double posY)
{
    cameraController.RotateCamera(posX, posY);
}

void scene::ShadowMapping::OnMouseScrolledEvent(double offsetX, double offsetY)
{
    cameraController.ZoomCamera(offsetX, offsetY);
}

void scene::ShadowMapping::OnRender()
{
    cameraController.SetCameraSensitvity(0.005);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.0f, far_plane = 7.5f;
    lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    //lightProjection = cameraController.getProjectionMatrix();
    lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;

    simpleDepthShader->Bind();
    simpleDepthShader->SetUniformMat4f("lightSpaceMatrix", lightSpaceMatrix);

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    texture->Bind();
    glCullFace(GL_FRONT);
    RenderScene(simpleDepthShader);
    glCullFace(GL_BACK); // don't forget to reset original culling face
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // reset viewport
    glViewport(0, 0, WIDTH, HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 2. render scene as normal using the generated depth/shadow map  
        // --------------------------------------------------------------
    if (debug) {
        debugDepthQuad->Bind();
        debugDepthQuad->SetUniform1f("near_plane", near_plane);
        debugDepthQuad->SetUniform1f("far_plane", far_plane);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        RenderQuad();
    }
    else {
        shader->Bind();
        glm::mat4 projection = glm::perspective(glm::radians(cameraController.GetCamera().Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = cameraController.GetViewMatrix();
        shader->SetUniformMat4f("projection", projection);
        shader->SetUniformMat4f("view", view);
        // set light uniforms
        shader->SetUniform3f("viewPos", cameraController.GetCameraPos());
        shader->SetUniform3f("lightPos", lightPos);
        shader->SetUniformMat4f("lightSpaceMatrix", lightSpaceMatrix);
        texture->Bind();
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        RenderScene(shader);
    } 
}

void scene::ShadowMapping::OnImGuiRender()
{
    ImGui::SliderFloat3("Light position", &lightPos[0], -10, 10);
    ImGui::Checkbox("Debug", &debug);
}

void scene::ShadowMapping::OnEvent(int event)
{
    cameraController.ProcessInput(event);
}

void scene::ShadowMapping::RenderScene(std::shared_ptr<Shader> shader)
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

void scene::ShadowMapping::RenderQuad()
{
    quadVAO->Bind();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
