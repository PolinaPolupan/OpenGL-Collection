#include "DiffuseIrradiance.h"

scene::DiffuseIrradiance::DiffuseIrradiance()
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

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;
    std::vector<float> data;

    const unsigned int X_SEGMENTS = 64;
    const unsigned int Y_SEGMENTS = 64;
    const float PI = 3.14159265359f;
    for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
    {
        for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
        {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

            positions.push_back(glm::vec3(xPos, yPos, zPos));
            uv.push_back(glm::vec2(xSegment, ySegment));
            normals.push_back(glm::vec3(xPos, yPos, zPos));
        }
    }

    bool oddRow = false;
    for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
    {
        if (!oddRow) // even rows: y == 0, y == 2; and so on
        {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
            {
                indices.push_back(y * (X_SEGMENTS + 1) + x);
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            }
        }
        else
        {
            for (int x = X_SEGMENTS; x >= 0; --x)
            {
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                indices.push_back(y * (X_SEGMENTS + 1) + x);
            }
        }
        oddRow = !oddRow;
    }


    for (unsigned int i = 0; i < positions.size(); ++i)
    {
        data.push_back(positions[i].x);
        data.push_back(positions[i].y);
        data.push_back(positions[i].z);
        if (normals.size() > 0)
        {
            data.push_back(normals[i].x);
            data.push_back(normals[i].y);
            data.push_back(normals[i].z);
        }
        if (uv.size() > 0)
        {
            data.push_back(uv[i].x);
            data.push_back(uv[i].y);
        }
    }

    sphereVAO = std::make_shared<VertexArray>();
    sphereVBO = std::make_shared<VertexBuffer>(&data[0], data.size() * sizeof(float));
    sphereIBO = std::make_shared<IndexBuffer>(&indices[0], indices.size() * sizeof(unsigned int));

    VertexBufferLayout sphereLayout;
    sphereLayout.Push<float>(3);
    sphereLayout.Push<float>(3);
    sphereLayout.Push<float>(2);

    sphereVAO->AddBuffer(*sphereVBO, sphereLayout);

    indexCount = static_cast<unsigned int>(indices.size());


    textures = getTextures({ ".hdr" });

    shader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\IBL.shader"));
    shaderTextured = std::make_shared<Shader>(GetResourcePath("res\\shaders\\IBLTextured.shader"));
    equirectangularToCubemapShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\EquirectangularToCubemap.shader"));
    backgroundShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\Background.shader"));
    irradianceShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\Irradiance.shader"));

    albedo = std::make_shared<Texture>(GetResourcePath("res\\textures\\pbr\\rusted_iron\\albedo.png"));
    roughness = std::make_shared<Texture>(GetResourcePath("res\\textures\\pbr\\rusted_iron\\roughness.png"));
    normal = std::make_shared<Texture>(GetResourcePath("res\\textures\\pbr\\rusted_iron\\normal.png"));
    metallic = std::make_shared<Texture>(GetResourcePath("res\\textures\\pbr\\rusted_iron\\metallic.png"));
    ao = std::make_shared<Texture>(GetResourcePath("res\\textures\\pbr\\rusted_iron\\ao.jpg"));
    hdr = std::make_shared<Texture>(GetResourcePath("res\\textures\\photo_studio_loft_hall_4k.hdr"));

    BakeIrradiance();

    shader->Bind();
    shader->SetUniform1i("irradianceMap", 0);
    shader->SetUniform3f("albedo", 0.5f, 0.0f, 0.0f);
    shader->SetUniform1f("ao", 1.0f);

    backgroundShader->Bind();
    backgroundShader->SetUniform1i("environmentMap", 0);

    shaderTextured->Bind();
    
    shaderTextured->SetUniform1i("irradianceMap", 0);
    shaderTextured->SetUniform1i("albedoMap", 1);
    shaderTextured->SetUniform1i("normalMap", 2);
    shaderTextured->SetUniform1i("metallicMap", 3);
    shaderTextured->SetUniform1i("roughnessMap", 4);
    shaderTextured->SetUniform1i("aoMap", 5);

    // lights
    // ------
    lightPositions = {
        glm::vec3(-10.0f,  10.0f, 10.0f),
        glm::vec3(10.0f,  10.0f, 10.0f),
        glm::vec3(-10.0f, -10.0f, 10.0f),
        glm::vec3(10.0f, -10.0f, 10.0f),
    };
    lightColors = {
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f)
    };


    // then before rendering, configure the viewport to the original framebuffer's screen dimensions
    glViewport(0, 0, WIDTH, HEIGHT);

    shader->Unbind();
    shaderTextured->Unbind();
    backgroundShader->Unbind();
    equirectangularToCubemapShader->Unbind();
    sphereVAO->Unbind();
    sphereVBO->Unbind();
    sphereIBO->Unbind();
    albedo->Unbind();
    roughness->Unbind();
    normal->Unbind();
    metallic->Unbind();
    ao->Unbind();
}

scene::DiffuseIrradiance::~DiffuseIrradiance()
{
    shader->Unbind();
    shaderTextured->Unbind();
    backgroundShader->Unbind();
    equirectangularToCubemapShader->Unbind();
    sphereVAO->Unbind();
    sphereVBO->Unbind();
    sphereIBO->Unbind();
    albedo->Unbind();
    roughness->Unbind();
    normal->Unbind();
    metallic->Unbind();
    ao->Unbind();
}

void scene::DiffuseIrradiance::OnUpdate(float deltaTime)
{
    cameraController.OnUpdate(deltaTime);
}

void scene::DiffuseIrradiance::OnMouseMovedEvent(double posX, double posY)
{
    cameraController.RotateCamera(posX, posY);
}

void scene::DiffuseIrradiance::OnMouseScrolledEvent(double offsetX, double offsetY)
{
}

void scene::DiffuseIrradiance::OnRender()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer.Submit(cameraController.GetCamera());

    cameraController.GetCamera().Sensitivity = 0.005f;
    cameraController.GetCamera().CameraSpeed = 5;

    shader->Bind();
    glm::mat4 view = cameraController.GetViewMatrix();
    renderer.Submit(cameraController.GetCamera());
    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    shader->SetUniformMat4f("projection", projection);
    shader->SetUniformMat4f("view", view);
    shader->SetUniform3f("camPos", cameraController.GetCameraPos());

    shaderTextured->Bind();
    shaderTextured->SetUniformMat4f("projection", projection);
    shaderTextured->SetUniformMat4f("view", view);
    shaderTextured->SetUniform3f("camPos", cameraController.GetCameraPos());

    // bind pre-computed IBL data
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);

    // render rows*column number of spheres with varying metallic/roughness values scaled by rows and columns respectively
    glm::mat4 model = glm::mat4(1.0f);

    if (textured) {
        albedo->Bind(1);
        normal->Bind(2);
        metallic->Bind(3);
        roughness->Bind(4);
        ao->Bind(5);

        for (int row = 0; row < nrRows; ++row)
        {
            for (int col = 0; col < nrColumns; ++col)
            {
                shaderTextured->Bind();

                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(
                    (col - (nrColumns / 2)) * spacing,
                    (row - (nrRows / 2)) * spacing,
                    0.0f
                ));
                shaderTextured->SetUniformMat4f("model", model);
                shaderTextured->SetUniformMat3f("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
                sphereVAO->Bind();
                glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
            }
        }

        // render light source (simply re-render sphere at light positions)
    // this looks a bit off as we use the same shader, but it'll make their positions obvious and 
    // keeps the codeprint small.
        for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
        {
            shaderTextured->Bind();
            glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
            newPos = lightPositions[i];
            shaderTextured->SetUniform3f("lightPositions[" + std::to_string(i) + "]", newPos);
            shaderTextured->SetUniform3f("lightColors[" + std::to_string(i) + "]", lightColors[i]);

            model = glm::mat4(1.0f);
            model = glm::translate(model, newPos);
            model = glm::scale(model, glm::vec3(0.5f));
            shaderTextured->SetUniformMat4f("model", model);
            shaderTextured->SetUniformMat3f("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
            sphereVAO->Bind();
            glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
        }
    }
    else {
        for (int row = 0; row < nrRows; ++row)
        {
            shader->Bind();
            shader->SetUniform1f("metallic", (float)row / (float)nrRows);
            for (int col = 0; col < nrColumns; ++col)
            {
                shader->Bind();
                // we clamp the roughness to 0.05 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off
                // on direct lighting.
                shader->SetUniform1f("roughness", glm::clamp((float)col / (float)nrColumns, 0.05f, 1.0f));

                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(
                    (col - (nrColumns / 2)) * spacing,
                    (row - (nrRows / 2)) * spacing,
                    0.0f
                ));
                shader->SetUniformMat4f("model", model);
                shader->SetUniformMat3f("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
                sphereVAO->Bind();
                glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
            }
        }

        // render light source (simply re-render sphere at light positions)
    // this looks a bit off as we use the same shader, but it'll make their positions obvious and 
    // keeps the codeprint small.
        for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
        {
            shader->Bind();
            glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
            newPos = lightPositions[i];
            shader->SetUniform3f("lightPositions[" + std::to_string(i) + "]", newPos);
            shader->SetUniform3f("lightColors[" + std::to_string(i) + "]", lightColors[i]);

            model = glm::mat4(1.0f);
            model = glm::translate(model, newPos);
            model = glm::scale(model, glm::vec3(0.5f));
            shader->SetUniformMat4f("model", model);
            shader->SetUniformMat3f("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
            sphereVAO->Bind();
            glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
        }
    }

    equirectangularToCubemapShader->Bind();
    view = glm::mat4(glm::mat3(cameraController.GetViewMatrix())); // remove translation from the view matrix
    equirectangularToCubemapShader->SetUniformMat4f("view", view);
    equirectangularToCubemapShader->SetUniform1f("alpha", 1.0f - transparency);
    hdr->Bind();
    renderer.Draw(*cubeVAO, *cubeIBO, *equirectangularToCubemapShader);
}

void scene::DiffuseIrradiance::OnImGuiRender()
{
    static bool checked = false;
    ImGui::Checkbox("Textured", &checked);

    textured = checked;

    ImGui::SliderFloat("Transparency", &transparency, 0.0f, 1.0f);

    for (int i = 0; i < textures.size(); i++)
    {
        if (i % 3 == 0)
        {
            ImGui::NewLine();
        }
        else
        {
            ImGui::SameLine();
        }
        if (ImGui::ImageButton(textures[i]->GetPath().c_str(), (void*)textures[i]->GetId(), ImVec2(50, 50)))
        {
           hdr = std::make_shared<Texture>(textures[i]->GetPath());
           BakeIrradiance();
        }
    }
}

void scene::DiffuseIrradiance::OnEvent(int event)
{
    cameraController.ProcessInput(event);
}

void scene::DiffuseIrradiance::BakeIrradiance()
{
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); // set depth function to less than AND equal for skybox depth trick.

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // pbr: setup framebuffer
    // ----------------------
    glGenFramebuffers(1, &captureFBO);
    glGenRenderbuffers(1, &captureRBO);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);

    // pbr: setup cubemap to render to and attach to framebuffer
   // ---------------------------------------------------------
    glGenTextures(1, &envCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA16F, 512, 512, 0, GL_RGBA, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    

    // pbr: set up projection and view matrices for capturing data onto the 6 cubemap face directions
    // ----------------------------------------------------------------------------------------------
    glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f);
    glm::mat4 captureViews[] =
    {
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
    };
    // pbr: convert HDR equirectangular environment map to cubemap equivalent
    // ----------------------------------------------------------------------
    equirectangularToCubemapShader->Bind();
    equirectangularToCubemapShader->SetUniform1f("alpha", 1.0f);
    equirectangularToCubemapShader->SetUniform1i("equirectangularMap", 0);
    equirectangularToCubemapShader->SetUniformMat4f("projection", captureProjection);
    hdr->Bind();

    glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for (unsigned int i = 0; i < 6; ++i)
    {
        equirectangularToCubemapShader->Bind();
        equirectangularToCubemapShader->SetUniformMat4f("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.Draw(*cubeVAO, *cubeIBO, *equirectangularToCubemapShader);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // pbr: create an irradiance cubemap, and re-scale capture FBO to irradiance scale.
    // --------------------------------------------------------------------------------
    glGenTextures(1, &irradianceMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA16F, 32, 32, 0, GL_RGBA, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);

    // pbr: solve diffuse integral by convolution to create an irradiance (cube)map.
    // -----------------------------------------------------------------------------
    irradianceShader->Bind();
    irradianceShader->SetUniform1i("environmentMap", 0);
    irradianceShader->SetUniformMat4f("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glViewport(0, 0, 32, 32); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for (unsigned int i = 0; i < 6; ++i)
    {
        irradianceShader->Bind();
        irradianceShader->SetUniformMat4f("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.Draw(*cubeVAO, *cubeIBO, *irradianceShader);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // then before rendering, configure the viewport to the original framebuffer's screen dimensions
    glViewport(0, 0, WIDTH, HEIGHT);
}
