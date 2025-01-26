#include "SSAO.h"

float ourLerp(float a, float b, float f)
{
    return a + f * (b - a);
}

scene::SSAO::SSAO()
{
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

    VertexBufferLayout cubeLayout;
    cubeLayout.Push<float>(3);
    cubeLayout.Push<float>(3);
    cubeLayout.Push<float>(2);

    cubeVAO->AddBuffer(*cubeVBO, cubeLayout);

    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    unsigned int quadIndices[] = { 0, 1, 2, 3, 4, 5 };

    quadVAO = std::make_shared<VertexArray>();
    quadVBO = std::make_shared<VertexBuffer>(quadVertices, sizeof(quadVertices));
    quadIBO = std::make_shared<IndexBuffer>(quadIndices, sizeof(quadIndices));

    VertexBufferLayout quadLayout;
    quadLayout.Push<float>(2);
    quadLayout.Push<float>(2);

    quadVAO->AddBuffer(*quadVBO, quadLayout);

    modelsPaths = getObjectsPath();

    shaderGeometryPass = std::make_shared<Shader>(GetResourcePath("res\\shaders\\SSAOGeometry.shader"));
    shaderLightingPass = std::make_shared<Shader>(GetResourcePath("res\\shaders\\SSAOLighting.shader"));
    shaderSSAO = std::make_shared<Shader>(GetResourcePath("res\\shaders\\SSAO.shader"));
    shaderSSAOBlur = std::make_shared<Shader>(GetResourcePath("res\\shaders\\SSAOBlur.shader"));
    shaderSSAOFlat = std::make_shared<Shader>(GetResourcePath("res\\shaders\\SSAOFlat.shader"));

    // configure g-buffer framebuffer
   // ------------------------------
    glGenFramebuffers(1, &gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    // position color buffer
    glGenTextures(1, &gPosition);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WIDTH, HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
    // normal color buffer
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WIDTH, HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
    // color + specular color buffer
    glGenTextures(1, &gAlbedo);
    glBindTexture(GL_TEXTURE_2D, gAlbedo);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedo, 0);
    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
    glDrawBuffers(3, attachments);
    // create and attach depth buffer (renderbuffer)
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WIDTH, HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // also create framebuffer to hold SSAO processing stage 
    // -----------------------------------------------------
    glGenFramebuffers(1, &ssaoFBO);  
    glGenFramebuffers(1, &ssaoBlurFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);
    // SSAO color buffer
    glGenTextures(1, &ssaoColorBuffer);
    glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, WIDTH, HEIGHT, 0, GL_RED, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBuffer, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "SSAO Framebuffer not complete!" << std::endl;
    // and blur stage
    glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFBO);
    glGenTextures(1, &ssaoColorBufferBlur);
    glBindTexture(GL_TEXTURE_2D, ssaoColorBufferBlur);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, WIDTH, HEIGHT, 0, GL_RED, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBufferBlur, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "SSAO Blur Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    generateSamples();

    glGenTextures(1, &noiseTexture);
    glBindTexture(GL_TEXTURE_2D, noiseTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 4, 4, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // shader configuration
    // --------------------
    shaderLightingPass->Bind();
    shaderLightingPass->SetUniform1i("gPosition", 0);
    shaderLightingPass->SetUniform1i("gNormal", 1);
    shaderLightingPass->SetUniform1i("gAlbedo", 2);
    shaderLightingPass->SetUniform1i("ssao", 3);
    shaderSSAO->Bind();
    shaderSSAO->SetUniform1i("gPosition", 0);
    shaderSSAO->SetUniform1i("gNormal", 1);
    shaderSSAO->SetUniform1i("texNoise", 2);
    shaderSSAOBlur->Bind();
    shaderSSAOBlur->SetUniform1i("ssaoInput", 0);
    shaderSSAOFlat->Bind();
    shaderSSAOFlat->SetUniform1i("ssao", 0);

    cubeVAO->Unbind();
    cubeVBO->Unbind();
    cubeIBO->Unbind();
    quadVAO->Unbind();
    quadIBO->Unbind();
    quadVBO->Unbind();
    shaderGeometryPass->Unbind();
    shaderSSAO->Unbind();
    shaderLightingPass->Unbind();
    shaderSSAOBlur->Unbind();
    shaderSSAOFlat->Unbind();
    objectManager.Clear();
}

scene::SSAO::~SSAO()
{
    cubeVAO->Unbind();
    cubeVBO->Unbind();
    cubeIBO->Unbind();
    quadVAO->Unbind();
    quadIBO->Unbind();
    quadVBO->Unbind();
    shaderGeometryPass->Unbind();
    shaderSSAO->Unbind();
    shaderLightingPass->Unbind();
    shaderSSAOBlur->Unbind();
    shaderSSAOFlat->Unbind();
    objectManager.Clear();
}

void scene::SSAO::OnUpdate(float deltaTime)
{
	cameraController.OnUpdate(deltaTime);
	objectManager.Update();
}

void scene::SSAO::OnMouseMovedEvent(double posX, double posY)
{
	cameraController.RotateCamera(posX, posY);
}

void scene::SSAO::OnMouseScrolledEvent(double offsetX, double offsetY)
{
	cameraController.ZoomCamera(offsetX, offsetY);
}

void scene::SSAO::OnRender()
{
    // render
        // ------
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cameraController.GetCamera().Sensitivity = 0.005f;

    // 1. geometry pass: render scene's geometry/color data into gbuffer
    // -----------------------------------------------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer.Submit(cameraController.GetCamera());
    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = cameraController.GetViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    shaderGeometryPass->Bind();
    shaderGeometryPass->SetUniformMat4f("projection", projection);
    shaderGeometryPass->SetUniformMat4f("view", view);
    // room cube
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0, 7.0f, 0.0f));
    model = glm::scale(model, glm::vec3(7.5f, 7.5f, 7.5f));
    shaderGeometryPass->SetUniformMat4f("model", model);
    shaderGeometryPass->SetUniform1i("invertedNormals", 1); // invert normals as we're inside the cube
    renderer.Draw(*cubeVAO, *cubeIBO, *shaderGeometryPass);
    shaderGeometryPass->Bind();
    shaderGeometryPass->SetUniform1i("invertedNormals", 0);
    // backpack model on the floor
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
    model = glm::scale(model, glm::vec3(1.0f));
    shaderGeometryPass->SetUniformMat4f("model", model);
    for (auto& o : objectManager.GetObjects())
    {
        shaderGeometryPass->Bind();
        renderer.RenderObject(*o, *shaderGeometryPass);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    // 2. generate SSAO texture
    // ------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);
    glClear(GL_COLOR_BUFFER_BIT);
    shaderSSAO->Bind();
    shaderSSAO->SetUniform1f("width", WIDTH);
    shaderSSAO->SetUniform1f("height", HEIGHT);
    shaderSSAO->SetUniform1f("radius", radius);
    shaderSSAO->SetUniform1f("bias", bias);
    shaderSSAO->SetUniform1i("kernelSize", samples);
    // Send kernel + rotation 
    for (unsigned int i = 0; i < samples; ++i) {
        shaderSSAO->Bind();
        shaderSSAO->SetUniform3f("samples[" + std::to_string(i) + "]", ssaoKernel[i]);
    }
        
    shaderSSAO->SetUniformMat4f("projection", projection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, noiseTexture);
    renderer.Draw(*quadVAO, *quadIBO, *shaderSSAO);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 3. blur SSAO texture to remove noise
    // ------------------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFBO);
    glClear(GL_COLOR_BUFFER_BIT);
    shaderSSAOBlur->Bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
    renderer.Draw(*quadVAO, *quadIBO, *shaderSSAOBlur);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (light) {
        // 4. lighting pass: traditional deferred Blinn-Phong lighting with added screen-space ambient occlusion
    // -----------------------------------------------------------------------------------------------------
        shaderLightingPass->Bind();
        // send light relevant uniforms
        glm::vec3 lightPosView = glm::vec3(cameraController.GetViewMatrix() * glm::vec4(lightPos, 1.0));
        shaderLightingPass->SetUniform3f("light.Position", lightPosView);
        shaderLightingPass->SetUniform3f("light.Color", lightColor);
        // Update attenuation parameters
        const float linear = 0.09f;
        const float quadratic = 0.032f;
        shaderLightingPass->SetUniform1f("light.Linear", linear);
        shaderLightingPass->SetUniform1f("light.Quadratic", quadratic);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gPosition);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, gAlbedo);
        glActiveTexture(GL_TEXTURE3); // add extra SSAO texture to lighting pass
        if (blur) glBindTexture(GL_TEXTURE_2D, ssaoColorBufferBlur);
        else glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
        renderer.Draw(*quadVAO, *quadIBO, *shaderLightingPass);
    } else {
        shaderSSAOFlat->Bind();
        glActiveTexture(GL_TEXTURE0); // add extra SSAO texture to lighting pass
        if (blur) glBindTexture(GL_TEXTURE_2D, ssaoColorBufferBlur);
        else glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
        renderer.Draw(*quadVAO, *quadIBO, *shaderSSAOFlat);
    }
}

void scene::SSAO::OnImGuiRender()
{
    LoadObjectsList(modelsPaths, objectManager);

    static bool ssao = false;
    static bool ssaoBlur = true;

    ImGui::Checkbox("SSAO", &ssao);
    ImGui::Checkbox("Blur", &ssaoBlur);
    ImGui::SliderFloat("Radius", &radius, 0, 10);
    ImGui::SliderFloat("Bias", &bias, 0, 1);
    if (ImGui::SliderInt("Samples", &samples, 0, 300)) {
        generateSamples();
    }

    light = !ssao;
    blur = ssaoBlur;
}

void scene::SSAO::OnEvent(int event)
{
	cameraController.ProcessInput(event);
}

void scene::SSAO::generateSamples()
{
    ssaoKernel.clear();
    ssaoNoise.clear();
    // generate sample kernel
    // ----------------------
    std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0); // generates random floats between 0.0 and 1.0
    std::default_random_engine generator;
    for (unsigned int i = 0; i < samples; ++i)
    {
        glm::vec3 sample(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, randomFloats(generator));
        sample = glm::normalize(sample);
        sample *= randomFloats(generator);
        float scale = float(i) / (float)samples;

        // scale samples s.t. they're more aligned to center of kernel
        scale = ourLerp(0.1f, 1.0f, scale * scale);
        sample *= scale;
        ssaoKernel.push_back(sample);
    }

    // generate noise texture
    // ----------------------
    for (unsigned int i = 0; i < 16; i++)
    {
        glm::vec3 noise(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, 0.0f); // rotate around z-axis (in tangent space)
        ssaoNoise.push_back(noise);
    }
}

