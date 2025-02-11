#include <functional>

#include "SpecularIBL.h"

scene::SpecularIBL::SpecularIBL()
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

    hdr = std::make_shared<Texture>(GetResourcePath("res\\textures\\photo_studio_loft_hall_4k.hdr"));

    albedoTexture = std::make_shared<Texture>(GetResourcePath("res\\textures\\container.jpg"));
    metallicTexture = std::make_shared<Texture>(GetResourcePath("res\\textures\\container.jpg"));
    roughnessTexture = std::make_shared<Texture>(GetResourcePath("res\\textures\\container.jpg"));
    normalTexture = std::make_shared<Texture>(GetResourcePath("res\\textures\\container.jpg"));
    aoTexture = std::make_shared<Texture>(GetResourcePath("res\\textures\\container.jpg"));

    Texture::Parameters envParameters;
    envParameters = envParameters.DefaultCubeMap();
    envParameters.minFilter = GL_LINEAR_MIPMAP_LINEAR;

    Texture::Builder envBuilder;
    envBuilder
        .SetTarget(GL_TEXTURE_CUBE_MAP)
        .SetInternalFormat(GL_RGB16F)
        .SetType(GL_FLOAT)
        .SetParameters(envParameters)
        .SetSize(512, 512);

    envCubemapTexture = std::make_shared<Texture>(envBuilder);

    Texture::Parameters irrParameters;
    irrParameters = irrParameters.DefaultCubeMap();

    Texture::Builder builder;
    builder
        .SetTarget(GL_TEXTURE_CUBE_MAP)
        .SetInternalFormat(GL_RGB16F)
        .SetType(GL_FLOAT)
        .SetParameters(irrParameters)
        .SetSize(32, 32);
  
    irradianceMapTexture = std::make_shared<Texture>(builder);


    Texture::Parameters prefilterParameters;
    prefilterParameters = prefilterParameters.DefaultCubeMap();
    prefilterParameters.minFilter = GL_LINEAR_MIPMAP_LINEAR;

    Texture::Builder prefilterBuilder;
    prefilterBuilder
        .SetTarget(GL_TEXTURE_CUBE_MAP)
        .SetInternalFormat(GL_RGB16F)
        .SetType(GL_FLOAT)
        .SetParameters(prefilterParameters)
        .SetSize(128, 128);

    prefilterMapTexture = std::make_shared<Texture>(prefilterBuilder);

    Texture::Parameters brdfLUTParameters;
    brdfLUTParameters = brdfLUTParameters.Default2D();
    brdfLUTParameters.wrapS = GL_CLAMP_TO_EDGE;
    brdfLUTParameters.wrapT = GL_CLAMP_TO_EDGE;

    Texture::Builder brdfLUTBuilder;
    brdfLUTBuilder
        .SetInternalFormat(GL_RG16F)
        .SetDataFormat(GL_RG)
        .SetType(GL_FLOAT)
        .SetParameters(brdfLUTParameters)
        .SetSize(512, 512);

    brdfLUTTexture = std::make_shared<Texture>(brdfLUTBuilder);

    modelsPaths = GetObjectsPath();
    textures = GetTextures({ ".hdr" });
    mapTextures = GetTextures({ ".jpeg", ".jpg", ".png", ".tga"}, {"res/textures"});

    pbrShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\SpecularIBL\\PBRSpecular.shader"));
    pbrShaderTextured = std::make_shared<Shader>(GetResourcePath("res\\shaders\\SpecularIBL\\PBRSpecularTextured.shader"));
    equirectangularToCubemapShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\EquirectangularToCubemap.shader"));
    backgroundShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\Background.shader"));
    irradianceShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\Irradiance.shader"));
    prefilterShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\SpecularIBL\\Prefilter.shader"));
    brdfShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\SpecularIBL\\BRDF.shader"));

    albedoColor = glm::vec3(0.5, 0, 0);

    pbrShader->Bind();
    pbrShader->SetUniform1i("irradianceMap", 0);
    pbrShader->SetUniform1i("prefilterMap", 1);
    pbrShader->SetUniform1i("brdfLUT", 2);

    pbrShaderTextured->Bind();
    pbrShaderTextured->SetUniform1i("irradianceMap", 0);
    pbrShaderTextured->SetUniform1i("prefilterMap", 1);
    pbrShaderTextured->SetUniform1i("brdfLUT", 2);
    pbrShaderTextured->SetUniform1i("albedoMap", 3);
    pbrShaderTextured->SetUniform1i("normalMap", 4);
    pbrShaderTextured->SetUniform1i("metallicMap", 5);
    pbrShaderTextured->SetUniform1i("roughnessMap", 6);
    pbrShaderTextured->SetUniform1i("aoMap", 7);

    backgroundShader->Bind();
    backgroundShader->SetUniform1i("environmentMap", 0);

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
    int nrRows = 7;
    int nrColumns = 7;
    float spacing = 2.5;

    BakeMaps();

    cubeVAO->Unbind();
    cubeIBO->Unbind();
    cubeVBO->Unbind();
    sphereVAO->Unbind();
    sphereIBO->Unbind();
    sphereVBO->Unbind();
    quadVAO->Unbind();
    quadVBO->Unbind();
    quadIBO->Unbind();
    pbrShader->Unbind();
    pbrShaderTextured->Unbind();
    equirectangularToCubemapShader->Unbind();
    backgroundShader->Unbind();
    irradianceShader->Unbind();
    prefilterShader->Unbind();
    brdfShader->Unbind();
    hdr->Unbind();
}

scene::SpecularIBL::~SpecularIBL()
{
    cubeVAO->Unbind();
    cubeIBO->Unbind();
    cubeVBO->Unbind();
    sphereVAO->Unbind();
    sphereIBO->Unbind();
    sphereVBO->Unbind();
    quadVAO->Unbind();
    quadVBO->Unbind();
    quadIBO->Unbind();
    pbrShader->Unbind();
    pbrShaderTextured->Unbind();
    equirectangularToCubemapShader->Unbind();
    backgroundShader->Unbind();
    irradianceShader->Unbind();
    prefilterShader->Unbind();
    brdfShader->Unbind();
    hdr->Unbind();
    objectManager.Clear();
}

void scene::SpecularIBL::OnUpdate(float deltaTime)
{
	cameraController.OnUpdate(deltaTime);
    objectManager.Update();
}

void scene::SpecularIBL::OnMouseMovedEvent(double posX, double posY)
{
	cameraController.RotateCamera(posX, posY);
}

void scene::SpecularIBL::OnMouseScrolledEvent(double offsetX, double offsetY)
{
}

void scene::SpecularIBL::OnRender()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer.Submit(cameraController.GetCamera());

    cameraController.GetCamera().Sensitivity = 0.005f;

    glm::mat4 view = cameraController.GetViewMatrix();

    if (!textured) {
        // render scene, supplying the convoluted irradiance map to the final shader.
        // ------------------------------------------------------------------------------------------
        pbrShader->Bind();
        renderer.Submit(cameraController.GetCamera());
        pbrShader->SetUniformMat4f("view", view);
        pbrShader->SetUniform3f("camPos", cameraController.GetCameraPos());

        glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        pbrShader->SetUniformMat4f("projection", projection);

        pbrShader->SetUniform3f("albedo", albedoColor);

        // bind pre-computed IBL data
        irradianceMapTexture->Bind();
        prefilterMapTexture->Bind(1);
        brdfLUTTexture->Bind(2);

        // render rows*column number of spheres with varying metallic/roughness values scaled by rows and columns respectively
        glm::mat4 model = glm::mat4(1.0f);

        pbrShader->Bind();
        pbrShader->SetUniform1f("metallic", metallic);
        pbrShader->SetUniform1f("roughness", roughness);
        pbrShader->SetUniform1f("ao", ao);
        pbrShader->SetUniformMat4f("model", model);
        pbrShader->SetUniformMat3f("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
        sphereVAO->Bind();
        glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);


        // render light source (simply re-render sphere at light positions)
        // this looks a bit off as we use the same shader, but it'll make their positions obvious and 
        // keeps the codeprint small.
        for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
        {
            pbrShader->Bind();
            glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
            newPos = lightPositions[i];
            pbrShader->SetUniform3f("lightPositions[" + std::to_string(i) + "]", newPos);
            pbrShader->SetUniform3f("lightColors[" + std::to_string(i) + "]", lightColors[i]);

            model = glm::mat4(1.0f);
            model = glm::translate(model, newPos);
            model = glm::scale(model, glm::vec3(0.5f));
            pbrShader->SetUniformMat4f("model", model);
            pbrShader->SetUniformMat3f("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
            sphereVAO->Bind();
            glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
        }
    } else {
        // render scene, supplying the convoluted irradiance map to the final shader.
        // ------------------------------------------------------------------------------------------
        pbrShaderTextured->Bind();
        renderer.Submit(cameraController.GetCamera());
        
        pbrShaderTextured->SetUniformMat4f("view", view);
        pbrShaderTextured->SetUniform3f("camPos", cameraController.GetCameraPos());

        glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        pbrShaderTextured->SetUniformMat4f("projection", projection);

        pbrShaderTextured->SetUniform3f("albedo", albedoColor);

        // bind pre-computed IBL data
        irradianceMapTexture->Bind();
        prefilterMapTexture->Bind(1);
        brdfLUTTexture->Bind(2);
        albedoTexture->Bind(3);
        normalTexture->Bind(4);
        metallicTexture->Bind(5);
        roughnessTexture->Bind(6);
        aoTexture->Bind(7);

        // render rows*column number of spheres with varying metallic/roughness values scaled by rows and columns respectively
        glm::mat4 model = glm::mat4(1.0f);

        pbrShaderTextured->Bind();
        pbrShaderTextured->SetUniform1f("metallic", metallic);
        pbrShaderTextured->SetUniform1f("roughness", roughness);
        pbrShaderTextured->SetUniform1f("ao", ao);
        pbrShaderTextured->SetUniformMat4f("model", model);
        pbrShaderTextured->SetUniformMat3f("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));

        for (auto& o : objectManager.GetObjects()) {
            pbrShaderTextured->Bind();
            renderer.RenderObject(*o, *pbrShaderTextured);
        }


        // render light source (simply re-render sphere at light positions)
        // this looks a bit off as we use the same shader, but it'll make their positions obvious and 
        // keeps the codeprint small.
        for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
        {
            pbrShaderTextured->Bind();
            glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
            newPos = lightPositions[i];
            pbrShaderTextured->SetUniform3f("lightPositions[" + std::to_string(i) + "]", newPos);
            pbrShaderTextured->SetUniform3f("lightColors[" + std::to_string(i) + "]", lightColors[i]);

            model = glm::mat4(1.0f);
            model = glm::translate(model, newPos);
            model = glm::scale(model, glm::vec3(0.5f));
            pbrShaderTextured->SetUniformMat4f("model", model);
            pbrShaderTextured->SetUniformMat3f("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
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



    // render BRDF map to screen
    //brdfShader.Use();
    //renderQuad();
}



void scene::SpecularIBL::OnImGuiRender()
{
    static bool showMaps = false;
    static bool checked = false;
    ImGui::Checkbox("Textured", &checked);

    textured = checked;
    static std::function<void()> storedFunction; 

    LoadObjectsList(modelsPaths, objectManager);

    ImGui::SliderFloat("Transparency", &transparency, 0.0f, 1.0f);
    ImGui::ColorEdit3("Albedo color", &albedoColor[0]);
    ImGui::SliderFloat("Roughness", &roughness, 0.0f, 1.0f);
    ImGui::SliderFloat("Metallic", &metallic, 0.0f, 1.0f);
    ImGui::SliderFloat("Ao", &ao, 0.0f, 1.0f);

    if (showMaps && storedFunction) {
        ImGui::Begin("Textures", &showMaps, ImGuiWindowFlags_MenuBar);
        storedFunction();
        ImGui::End();
    }

    ImGui::Text("Albedo texture");
    ImGui::PushID("Albedo texture");
    if (ImGui::ImageButton(albedoTexture->GetPath().c_str(), (void*)albedoTexture->GetId(), ImVec2(50, 50))) {
        showMaps = true;
        storedFunction = [&]() { MapBrowser(albedoTexture); };
    }
    ImGui::PopID();

    ImGui::Text("Roughness texture");
    ImGui::PushID("Roughness texture");
    if (ImGui::ImageButton(roughnessTexture->GetPath().c_str(), (void*)roughnessTexture->GetId(), ImVec2(50, 50))) {
        showMaps = true;
        storedFunction = [&]() { MapBrowser(roughnessTexture); };
    }
    ImGui::PopID();

    ImGui::Text("Metallic texture");
    ImGui::PushID("Metallic texture");
    if (ImGui::ImageButton(metallicTexture->GetPath().c_str(), (void*)metallicTexture->GetId(), ImVec2(50, 50))) {
        showMaps = true;
        storedFunction = [&]() { MapBrowser(metallicTexture); };
    }
    ImGui::PopID();

    ImGui::Text("Normal texture");
    ImGui::PushID("Normal texture");
    if (ImGui::ImageButton(normalTexture->GetPath().c_str(), (void*)normalTexture->GetId(), ImVec2(50, 50))) {
        showMaps = true;
        storedFunction = [&]() { MapBrowser(normalTexture); };
    }
    ImGui::PopID();

    ImGui::Text("Ao texture");
    ImGui::PushID("Ao texture");
    if (ImGui::ImageButton(aoTexture->GetPath().c_str(), (void*)aoTexture->GetId(), ImVec2(50, 50))) {
        showMaps = true;
        storedFunction = [&]() { MapBrowser(aoTexture); };
    }
    ImGui::PopID();

    for (int i = 0; i < textures.size(); i++) {
        if (i % 3 == 0) ImGui::NewLine();
        else ImGui::SameLine();
        if (ImGui::ImageButton(textures[i]->GetPath().c_str(), (void*)textures[i]->GetId(), ImVec2(50, 50))) {
            hdr = std::make_shared<Texture>(textures[i]->GetPath());
            BakeMaps();
        }
    }
}

void scene::SpecularIBL::MapBrowser(std::shared_ptr<Texture>& texture)
{
    for (int i = 0; i < mapTextures.size(); i++) {
        if (i % 3 == 0) ImGui::NewLine();
        else ImGui::SameLine();
        if (ImGui::ImageButton(mapTextures[i]->GetPath().c_str(), (void*)mapTextures[i]->GetId(), ImVec2(50, 50))) {
            texture = std::make_shared<Texture>(mapTextures[i]->GetPath());
        }
    }  
}

void scene::SpecularIBL::OnEvent(int event)
{
	cameraController.ProcessInput(event);
}

void scene::SpecularIBL::BakeMaps()
{
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); // set depth function to less than AND equal for skybox depth trick.

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // pbr: setup framebuffer
    // ----------------------
    captureFBO = std::make_shared<Framebuffer>();
    captureRBO = std::make_shared<Renderbuffer>();

    captureFBO->Bind();
    captureRBO->Bind();
    captureRBO->SetStorage(GL_DEPTH_COMPONENT24, 512, 512);
    captureFBO->AttachRenderBuffer(*captureRBO, GL_DEPTH_ATTACHMENT);

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
    equirectangularToCubemapShader->SetUniform1i("equirectangularMap", 0);
    equirectangularToCubemapShader->SetUniformMat4f("projection", captureProjection);
    hdr->Bind();
    glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
    captureFBO->Bind();
    for (unsigned int i = 0; i < 6; ++i)
    {
        equirectangularToCubemapShader->Bind();
        equirectangularToCubemapShader->SetUniformMat4f("view", captureViews[i]);
        captureFBO->AttachTexture(*envCubemapTexture, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.Draw(*cubeVAO, *cubeIBO, *equirectangularToCubemapShader);
    }
    captureFBO->Unbind();

    // then let OpenGL generate mipmaps from first mip face (combatting visible dots artifact)
    envCubemapTexture->Bind();
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    captureFBO->Bind();
    captureRBO->Bind();
    captureRBO->SetStorage(GL_DEPTH_COMPONENT24, 32, 32);

    // pbr: solve diffuse integral by convolution to create an irradiance (cube)map.
    // -----------------------------------------------------------------------------
    irradianceShader->Bind();
    irradianceShader->SetUniform1i("environmentMap", 0);
    irradianceShader->SetUniformMat4f("projection", captureProjection);
    
    envCubemapTexture->Bind();

    glViewport(0, 0, 32, 32); // don't forget to configure the viewport to the capture dimensions.
    captureFBO->Bind();
    for (unsigned int i = 0; i < 6; ++i)
    {
        irradianceShader->Bind();
        irradianceShader->SetUniformMat4f("view", captureViews[i]);
        captureFBO->AttachTexture(*irradianceMapTexture, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.Draw(*cubeVAO, *cubeIBO, *irradianceShader);
    }
    captureFBO->Unbind();

    // pbr: run a quasi monte-carlo simulation on the environment lighting to create a prefilter (cube)map.
    // ----------------------------------------------------------------------------------------------------
    prefilterShader->Bind();
    prefilterShader->SetUniform1i("environmentMap", 0);
    prefilterShader->SetUniformMat4f("projection", captureProjection);
    envCubemapTexture->Bind();

    captureFBO->Bind();
    unsigned int maxMipLevels = 5;
    for (unsigned int mip = 0; mip < maxMipLevels; ++mip)
    {
        prefilterShader->Bind();
        // reisze framebuffer according to mip-level size.
        unsigned int mipWidth = static_cast<unsigned int>(128 * std::pow(0.5, mip));
        unsigned int mipHeight = static_cast<unsigned int>(128 * std::pow(0.5, mip));
        captureRBO->Bind();
        captureRBO->SetStorage(GL_DEPTH_COMPONENT24, mipWidth, mipHeight);
        glViewport(0, 0, mipWidth, mipHeight);

        float roughness = (float)mip / (float)(maxMipLevels - 1);
        prefilterShader->SetUniform1f("roughness", roughness);
        for (unsigned int i = 0; i < 6; ++i)
        {
            prefilterShader->Bind();
            prefilterShader->SetUniformMat4f("view", captureViews[i]);
            captureFBO->AttachTexture(*prefilterMapTexture, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, mip);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            renderer.Draw(*cubeVAO, *cubeIBO, *prefilterShader);
        }
    }
    captureFBO->Unbind();

    // then re-configure capture framebuffer object and render screen-space quad with BRDF shader.
    captureFBO->Bind();
    captureRBO->Bind();
    captureRBO->SetStorage(GL_DEPTH_COMPONENT24, 512, 512);
    captureFBO->AttachTexture(*brdfLUTTexture, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D);

    glViewport(0, 0, 512, 512);
    brdfShader->Bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer.Draw(*quadVAO, *quadIBO, *brdfShader);

    captureFBO->Unbind();

    glViewport(0, 0, WIDTH, HEIGHT);
}
