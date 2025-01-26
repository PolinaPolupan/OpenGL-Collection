#include "ParallaxMapping.h"

scene::ParallaxMapping::ParallaxMapping()
{
    glm::vec3 pos1(-1.0f, 1.0f, 0.0f);
    glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
    glm::vec3 pos3(1.0f, -1.0f, 0.0f);
    glm::vec3 pos4(1.0f, 1.0f, 0.0f);
    // texture coordinates
    glm::vec2 uv1(0.0f, 1.0f);
    glm::vec2 uv2(0.0f, 0.0f);
    glm::vec2 uv3(1.0f, 0.0f);
    glm::vec2 uv4(1.0f, 1.0f);
    // normal vector
    glm::vec3 nm(0.0f, 0.0f, 1.0f);

    // calculate tangent/bitangent vectors of both triangles
    glm::vec3 tangent1, bitangent1;
    glm::vec3 tangent2, bitangent2;
    // triangle 1
    // ----------
    glm::vec3 edge1 = pos2 - pos1;
    glm::vec3 edge2 = pos3 - pos1;
    glm::vec2 deltaUV1 = uv2 - uv1;
    glm::vec2 deltaUV2 = uv3 - uv1;

    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent1 = glm::normalize(tangent1);

    bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent1 = glm::normalize(bitangent1);

    // triangle 2
    // ----------
    edge1 = pos3 - pos1;
    edge2 = pos4 - pos1;
    deltaUV1 = uv3 - uv1;
    deltaUV2 = uv4 - uv1;

    f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent2 = glm::normalize(tangent2);


    bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent2 = glm::normalize(bitangent2);


    float planeVertices[] = {
        // positions            // normal         // texcoords  // tangent                          // bitangent
        pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
        pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
        pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

        pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
        pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
        pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
    };

    unsigned int planeIndices[] = { 0, 1, 2, 3, 4, 5 };

    diffuseMap = std::make_shared<Texture>(GetResourcePath("res\\textures\\bricks2.jpg"));
    normalMap = std::make_shared<Texture>(GetResourcePath("res\\textures\\bricks2_normal.jpg"));
    heightMap = std::make_shared<Texture>(GetResourcePath("res\\textures\\bricks2_disp.jpg"));

    planeShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\ParallaxMapping.shader"));

    planeShader->Bind();
    planeShader->SetUniform1i("material.diffuse1", 0);
    planeShader->SetUniform1i("material.normal1", 1);
    planeShader->SetUniform1i("material.height1", 2);

    planeVAO = std::make_shared<VertexArray>();
    planeVBO = std::make_shared<VertexBuffer>(planeVertices, sizeof(planeVertices));
    planeIBO = std::make_shared<IndexBuffer>(planeIndices, sizeof(planeIndices));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    layout.Push<float>(3);
    layout.Push<float>(3);

    planeVAO->AddBuffer(*planeVBO, layout);

    modelsPaths = getObjectsPath();

    planeVAO->Unbind();
    planeVBO->Unbind();
    planeIBO->Unbind();
    planeShader->Unbind();
    diffuseMap->Unbind();
    normalMap->Unbind();
    heightMap->Unbind();
}

scene::ParallaxMapping::~ParallaxMapping()
{
    planeVAO->Unbind();
    planeVBO->Unbind();
    planeIBO->Unbind();
    planeShader->Unbind();
    diffuseMap->Unbind();
    normalMap->Unbind();
    heightMap->Unbind();
    objectManager.Clear();
}

void scene::ParallaxMapping::OnUpdate(float deltaTime)
{
    cameraController.OnUpdate(deltaTime);
    objectManager.Update();
}

void scene::ParallaxMapping::OnMouseMovedEvent(double posX, double posY)
{
    cameraController.RotateCamera(posX, posY);
}

void scene::ParallaxMapping::OnMouseScrolledEvent(double offsetX, double offsetY)
{
    cameraController.ZoomCamera(offsetX, offsetY);
}

void scene::ParallaxMapping::OnRender()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer.Submit(cameraController.GetCamera());

    // configure view/projection matrices
    glm::mat4 projection = glm::perspective(glm::radians(cameraController.GetCamera().Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = cameraController.GetViewMatrix();
    planeShader->Bind();
    planeShader->SetUniformMat4f("projection", projection);
    planeShader->SetUniformMat4f("view", view);
    //  // render normal-mapped quad
    glm::mat4 model = glm::mat4(1.0f);
    planeShader->SetUniformMat4f("model", model);
    planeShader->SetUniform3f("viewPos", cameraController.GetCameraPos());
    planeShader->SetUniform3f("lightPos", lightPos);
    planeShader->SetUniform1f("heightScale", heightScale);
    
    RenderPlane();
   /* for (auto& o : objectManager.getObjects())
    {
        planeShader->Bind();
        renderer.RenderObject(*o, *planeShader);
    }*/
}

void scene::ParallaxMapping::OnImGuiRender()
{
    ImGui::SliderFloat3("light pos", &lightPos[0], -5, 5);
    ImGui::SliderFloat("height scale", &heightScale, 0, 1);
    LoadObjectsList(modelsPaths, objectManager);
}

void scene::ParallaxMapping::OnEvent(int event)
{
    cameraController.ProcessInput(event);
}

void scene::ParallaxMapping::RenderPlane()
{
    diffuseMap->Bind();
    normalMap->Bind(1);
    heightMap->Bind(2);
    renderer.Draw(*planeVAO, *planeIBO, *planeShader);
}
