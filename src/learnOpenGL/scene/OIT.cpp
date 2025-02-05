#include "OIT.h"

scene::OIT::OIT()
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


    float quadVertices[] = {
        // positions		// uv
        -1.0f, -1.0f, 0.0f,	0.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,

         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f
    };

    unsigned int quadIndices[] = { 0, 1, 2, 3, 4, 5 };

    quadVAO = std::make_shared<VertexArray>();
    quadVBO = std::make_shared<VertexBuffer>(quadVertices, sizeof(quadVertices));
    quadIBO = std::make_shared<IndexBuffer>(quadIndices, sizeof(quadIndices));

    VertexBufferLayout quadLayout;
    quadLayout.Push<float>(3);
    quadLayout.Push<float>(2);

    quadVAO->AddBuffer(*quadVBO, quadLayout);



    opaqueFBO = std::make_shared<Framebuffer>();

    Texture::Parameters parameters;
    Texture::Builder builder;
    builder
        .SetParameters(parameters)
        .SetInternalFormat(GL_RGBA16F)
        .SetSize(WIDTH, HEIGHT)
        .SetDataFormat(GL_RGBA)
        .SetType(GL_HALF_FLOAT);

    opaqueTexture = std::make_shared<Texture>(builder);

    builder
        .SetInternalFormat(GL_DEPTH_COMPONENT)
        .SetDataFormat(GL_DEPTH_COMPONENT)
        .SetType(GL_FLOAT);

    depthTexture = std::make_shared<Texture>(builder);

    opaqueFBO->AttachTexture(*opaqueTexture, GL_COLOR_ATTACHMENT0);
    opaqueFBO->AttachTexture(*depthTexture, GL_DEPTH_ATTACHMENT);
    opaqueFBO->Unbind();

    transparentFBO = std::make_shared<Framebuffer>();
    transparentFBO->Bind();

    builder
        .SetInternalFormat(GL_RGBA16F)
        .SetDataFormat(GL_RGBA)
        .SetType(GL_HALF_FLOAT);

    accumTexture = std::make_shared<Texture>(builder);

    builder
        .SetInternalFormat(GL_R8)
        .SetDataFormat(GL_RED)
        .SetType(GL_FLOAT);

    revealTexture = std::make_shared<Texture>(builder);

    transparentFBO->AttachTexture(*accumTexture, GL_COLOR_ATTACHMENT0);
    transparentFBO->AttachTexture(*revealTexture, GL_COLOR_ATTACHMENT1);
    transparentFBO->AttachTexture(*depthTexture, GL_DEPTH_ATTACHMENT);
    transparentFBO->DrawBuffers(2, { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 });



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

    Texture::Builder irrBuilder;
    irrBuilder
        .SetTarget(GL_TEXTURE_CUBE_MAP)
        .SetInternalFormat(GL_RGB16F)
        .SetType(GL_FLOAT)
        .SetParameters(irrParameters)
        .SetSize(32, 32);

    irradianceMapTexture = std::make_shared<Texture>(irrBuilder);


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



    solidShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\OIT\\Solid.shader"));
    transparentShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\OIT\\Transparent.shader"));
    compositeShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\OIT\\Composite.shader"));
    screenShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\OIT\\Screen.shader"));

    pbrShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\OIT\\PBR.shader"));
    pbrTransparentShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\OIT\\PBRTransparent.shader"));
    equirectangularToCubemapShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\OIT\\EquirectangularToCubemap.shader"));
    backgroundShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\OIT\\Background.shader"));
    irradianceShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\OIT\\Irradiance.shader"));
    prefilterShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\OIT\\Prefilter.shader"));
    brdfShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\OIT\\BRDF.shader"));

    hdr = std::make_shared<Texture>(GetResourcePath("res\\textures\\photo_studio_loft_hall_4k.hdr"));
    albedoTexture = std::make_shared<Texture>(GetResourcePath("res\\textures\\container.jpg"));
    metallicTexture = std::make_shared<Texture>(GetResourcePath("res\\textures\\container.jpg"));
    roughnessTexture = std::make_shared<Texture>(GetResourcePath("res\\textures\\container.jpg"));
    normalTexture = std::make_shared<Texture>(GetResourcePath("res\\textures\\container.jpg"));
    aoTexture = std::make_shared<Texture>(GetResourcePath("res\\textures\\container.jpg"));

    modelsPaths = GetObjectsPath();
    textures = GetTextures({ ".hdr" });
    mapTextures = GetTextures({ ".jpeg", ".jpg", ".png", ".tga" }, { "res/textures" });

    pbrShader->Bind();
    pbrShader->SetUniform1i("irradianceMap", 0);
    pbrShader->SetUniform1i("prefilterMap", 1);
    pbrShader->SetUniform1i("brdfLUT", 2);
    pbrShader->SetUniform1i("albedoMap", 3);
    pbrShader->SetUniform1i("normalMap", 4);
    pbrShader->SetUniform1i("metallicMap", 5);
    pbrShader->SetUniform1i("roughnessMap", 6);
    pbrShader->SetUniform1i("aoMap", 7);

    backgroundShader->Bind();
    backgroundShader->SetUniform1i("environmentMap", 0);

    BakeMaps();

    quadVAO->Unbind();
    quadIBO->Unbind();
    quadVBO->Unbind();
    cubeVAO->Unbind();
    cubeIBO->Unbind();
    cubeVBO->Unbind();
    opaqueFBO->Unbind();
    transparentFBO->Unbind();
    hdr->Unbind();
    opaqueTexture->Unbind();
    revealTexture->Unbind();
    depthTexture->Unbind();
    accumTexture->Unbind();
    albedoTexture->Unbind();
    metallicTexture->Unbind();
    roughnessTexture->Unbind();
    normalTexture->Unbind();
    aoTexture->Unbind();
    solidShader->Unbind();
    transparentShader->Unbind();
    compositeShader->Unbind();
    screenShader->Unbind();
    pbrShader->Unbind();
    equirectangularToCubemapShader->Unbind();
    backgroundShader->Unbind();
    irradianceShader->Unbind();
    prefilterShader->Unbind();
    brdfShader->Unbind();
}

scene::OIT::~OIT()
{
    renderer.Clear();
    objectManager.Clear();
    modelsPaths.clear();
    textures.clear();
    mapTextures.clear();
    quadVAO->Unbind();
    quadIBO->Unbind();
    quadVBO->Unbind();
    cubeVAO->Unbind();
    cubeIBO->Unbind();
    cubeVBO->Unbind();
    opaqueFBO->Unbind();
    transparentFBO->Unbind();
    hdr->Unbind();
    opaqueTexture->Unbind();
    revealTexture->Unbind();
    depthTexture->Unbind();
    accumTexture->Unbind();
    albedoTexture->Unbind();
    metallicTexture->Unbind();
    roughnessTexture->Unbind();
    normalTexture->Unbind();
    aoTexture->Unbind();
    solidShader->Unbind();
    transparentShader->Unbind();
    compositeShader->Unbind();
    screenShader->Unbind();
    pbrShader->Unbind();
    equirectangularToCubemapShader->Unbind();
    backgroundShader->Unbind();
    irradianceShader->Unbind();
    prefilterShader->Unbind();
    brdfShader->Unbind();
}

void scene::OIT::OnUpdate(float deltaTime)
{
    cameraController.OnUpdate(deltaTime);
    objectManager.Update();
    objectTransparentManager.Update();
}

void scene::OIT::OnMouseMovedEvent(double posX, double posY)
{
    cameraController.RotateCamera(posX, posY);
}

void scene::OIT::OnMouseScrolledEvent(double offsetX, double offsetY)
{
}

void scene::OIT::OnRender()
{
    renderer.Submit(cameraController.GetCamera());
    glm::mat4 view = cameraController.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

    if (PBR) {
      //  renderer.DisableBlending();

        opaqueFBO->Bind();
        renderer.ClearBuffer();
        RenderPBR(view, projection);
        opaqueFBO->Unbind();

        transparentFBO->Bind();

        renderer.EnableBlending();
        renderer.DisableDepthWriting();
        renderer.SetTargetBlendingFunction(0, GL_ONE, GL_ONE);
        renderer.SetTargetBlendingFunction(1, GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
        renderer.SetBlendingEquation(GL_FUNC_ADD);

        renderer.ClearTargetBufferFv(GL_COLOR, 0, glm::vec4(0.0f));
        renderer.ClearTargetBufferFv(GL_COLOR, 1, glm::vec4(1.0f));
        RenderPBRTransparent(view, projection);
        transparentFBO->Unbind();

        opaqueFBO->Bind();

        renderer.EnableBlending();
        //renderer.SetDepthFunction(GL_ALWAYS);
        renderer.SetBlendingFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        compositeShader->Bind();

        accumTexture->Bind(0);
        revealTexture->Bind(1);
        renderer.Draw(*quadVAO, *quadIBO, *compositeShader);

        opaqueFBO->Unbind();

       ///renderer.DisableDepthTesting();
        renderer.EnableDepthWriting();
        renderer.DisableBlending();
        renderer.ClearBuffer();

        screenShader->Bind();

        opaqueTexture->Bind();
        renderer.Draw(*quadVAO, *quadIBO, *screenShader);
    }
    else {
        renderer.Clear();
        renderer.EnableDepthTesting();
        renderer.DisableBlending();

        cameraController.GetCamera().Sensitivity = 0.005f;

        opaqueFBO->Bind();

        renderer.ClearBuffer();
        solidShader->Bind();
        solidShader->SetUniformMat4f("projection", projection);
        solidShader->SetUniformMat4f("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
        solidShader->SetUniformMat4f("model", model);
        solidShader->SetUniform3f("color", glm::vec3(1.0f, 0.0f, 0.0f));

        renderer.Draw(*quadVAO, *quadIBO, *solidShader);

        opaqueFBO->Unbind();


        transparentFBO->Bind();

        renderer.EnableBlending();
        renderer.DisableDepthWriting();
        renderer.SetTargetBlendingFunction(0, GL_ONE, GL_ONE);
        renderer.SetTargetBlendingFunction(1, GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
        renderer.SetBlendingEquation(GL_FUNC_ADD);

        renderer.ClearTargetBufferFv(GL_COLOR, 0, glm::vec4(0.0f));
        renderer.ClearTargetBufferFv(GL_COLOR, 1, glm::vec4(1.0f));

        transparentShader->Bind();
        transparentShader->SetUniformMat4f("projection", projection);
        transparentShader->SetUniformMat4f("view", view);
        model = glm::mat4(1.0f);
        transparentShader->SetUniformMat4f("model", model);
        transparentShader->SetUniform4f("color", glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));
        renderer.Draw(*quadVAO, *quadIBO, *transparentShader);

        transparentShader->Bind();
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 2.0f));
        transparentShader->SetUniformMat4f("model", model);
        transparentShader->SetUniform4f("color", glm::vec4(0.0f, 0.0f, 1.0f, 0.5f));
        renderer.Draw(*quadVAO, *quadIBO, *transparentShader);

        transparentFBO->Unbind();


        opaqueFBO->Bind();

        renderer.EnableBlending();
        renderer.SetDepthFunction(GL_ALWAYS);
        renderer.SetBlendingFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        compositeShader->Bind();

        accumTexture->Bind(0);
        revealTexture->Bind(1);
        renderer.Draw(*quadVAO, *quadIBO, *compositeShader);

        opaqueFBO->Unbind();

        renderer.DisableDepthTesting();
        renderer.EnableDepthWriting();
        renderer.DisableBlending();
        renderer.ClearBuffer();

        screenShader->Bind();

        opaqueTexture->Bind();
        renderer.Draw(*quadVAO, *quadIBO, *screenShader);
    } 
}

void scene::OIT::OnImGuiRender()
{
    if (ImGui::Checkbox("PBR", &PBR)) {
        if (PBR) BakeMaps();
    }
    if (PBR) {
        static bool showMaps = false;

        static std::function<void()> storedFunction;

        ImGui::Text("Load objects");
        ImGui::PushID("Load objects");
        LoadObjectsList(modelsPaths, objectManager);
        ImGui::PopID();
        ImGui::Text("Load transparent objects");
        ImGui::SliderFloat("Transparency", &transparency, 0.0f, 1.0f);
        ImGui::PushID("Load transparent objects");
        LoadObjectsList(modelsPaths, objectTransparentManager);
        ImGui::PopID();

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
}

void scene::OIT::MapBrowser(std::shared_ptr<Texture>& texture)
{
    for (int i = 0; i < mapTextures.size(); i++) {
        if (i % 3 == 0) ImGui::NewLine();
        else ImGui::SameLine();
        if (ImGui::ImageButton(mapTextures[i]->GetPath().c_str(), (void*)mapTextures[i]->GetId(), ImVec2(50, 50))) {
            texture = std::make_shared<Texture>(mapTextures[i]->GetPath());
        }
    }
}

void scene::OIT::ObjectUi(Model& object)
{
    ImGui::SliderFloat3("Position", &object.position[0], -20.f, 20.f);
    if (ImGui::SliderFloat("Scale1", &object.scale[0], 0, 1)) {
        object.scale[1] = object.scale[2] = object.scale[0];
    }
    ImGui::SliderFloat3("Scale", &object.scale[0], -20.f, 20.f);
   // ImGui::SliderFloat("Transparency", )
}

void scene::OIT::OnEvent(int event)
{
    cameraController.ProcessInput(event);
}

void scene::OIT::BakeMaps()
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
        renderer.ClearBuffer();
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
        renderer.ClearBuffer();
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
            renderer.ClearBuffer();
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
    renderer.ClearBuffer();
    renderer.Draw(*quadVAO, *quadIBO, *brdfShader);

    captureFBO->Unbind();

    glViewport(0, 0, WIDTH, HEIGHT);
}

void scene::OIT::RenderPBR(const glm::mat4& view, const glm::mat4& projection)
{
    // render scene, supplying the convoluted irradiance map to the final shader.
        // ------------------------------------------------------------------------------------------
    pbrShader->Bind();
    renderer.Submit(cameraController.GetCamera());

    pbrShader->SetUniformMat4f("view", view);
    pbrShader->SetUniform3f("camPos", cameraController.GetCameraPos());
    pbrShader->SetUniformMat4f("projection", projection);

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

    pbrShader->Bind();
    pbrShader->SetUniformMat4f("model", model);
    pbrShader->SetUniformMat3f("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));

    for (auto& o : objectManager.GetObjects()) {
        pbrShader->Bind();
        renderer.RenderObject(*o, *pbrShader);
    }
    hdr->Bind();
    equirectangularToCubemapShader->Bind();
    glm::mat4 viewTemp = glm::mat4(glm::mat3(cameraController.GetViewMatrix())); // remove translation from the view matrix
    equirectangularToCubemapShader->SetUniformMat4f("view", viewTemp);
    equirectangularToCubemapShader->SetUniform1f("alpha", 1.0f);
    renderer.Draw(*cubeVAO, *cubeIBO, *equirectangularToCubemapShader);
}

void scene::OIT::RenderPBRTransparent(const glm::mat4& view, const glm::mat4& projection)
{
    // render scene, supplying the convoluted irradiance map to the final shader.
        // ------------------------------------------------------------------------------------------
    pbrTransparentShader->Bind();
    renderer.Submit(cameraController.GetCamera());

    pbrTransparentShader->SetUniformMat4f("view", view);
    pbrTransparentShader->SetUniform3f("camPos", cameraController.GetCameraPos());
    pbrTransparentShader->SetUniformMat4f("projection", projection);

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

    pbrTransparentShader->Bind();
    pbrTransparentShader->SetUniformMat4f("model", model);
    pbrTransparentShader->SetUniformMat3f("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
    pbrTransparentShader->SetUniform1f("alpha", transparency);

    for (auto& o : objectTransparentManager.GetObjects()) {
        pbrTransparentShader->Bind();
        renderer.RenderObject(*o, *pbrTransparentShader);
    }
}
