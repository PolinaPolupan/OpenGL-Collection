#include "OIT.h"

scene::OIT::OIT()
{
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

    solidShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\OIT\\Solid.shader"));
    transparentShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\OIT\\Transparent.shader"));
    compositeShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\OIT\\Composite.shader"));
    screenShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\OIT\\Screen.shader"));

    quadVAO->Unbind();
    quadIBO->Unbind();
    quadVBO->Unbind();
    opaqueFBO->Unbind();
    transparentFBO->Unbind();
    opaqueTexture->Unbind();
    revealTexture->Unbind();
    depthTexture->Unbind();
    accumTexture->Unbind();
    solidShader->Unbind();
    transparentShader->Unbind();
    compositeShader->Unbind();
    screenShader->Unbind();
}

scene::OIT::~OIT()
{
    renderer.Clear();
    quadVAO->Unbind();
    quadIBO->Unbind();
    quadVBO->Unbind();
    opaqueFBO->Unbind();
    transparentFBO->Unbind();
    opaqueTexture->Unbind();
    revealTexture->Unbind();
    depthTexture->Unbind();
    accumTexture->Unbind();
    solidShader->Unbind();
    transparentShader->Unbind();
    compositeShader->Unbind();
    screenShader->Unbind();
}

void scene::OIT::OnUpdate(float deltaTime)
{
    cameraController.OnUpdate(deltaTime);
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
    renderer.Clear();
    renderer.EnableDepthTesting();
    renderer.DisableBlending();

    cameraController.GetCamera().Sensitivity = 0.005f;

    opaqueFBO->Bind();   

    renderer.ClearBuffer();
    solidShader->Bind();
    renderer.Submit(cameraController.GetCamera());
    glm::mat4 view = cameraController.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
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

void scene::OIT::OnImGuiRender()
{
}

void scene::OIT::OnEvent(int event)
{
    cameraController.ProcessInput(event);
}
