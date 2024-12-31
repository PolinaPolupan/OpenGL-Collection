#include "PBR.h"

scene::PBR::PBR()
{
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

    shader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\PBR.shader"));

    shader->Bind();
    shader->SetUniform3f("albedo", 0.5f, 0.0f, 0.0f);
    shader->SetUniform1f("ao", 1.0f);

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

    shader->Unbind();
    sphereVAO->Unbind();
    sphereVBO->Unbind();
    sphereIBO->Unbind();
}

scene::PBR::~PBR()
{
    shader->Unbind();
    sphereVAO->Unbind();
    sphereVBO->Unbind();
    sphereIBO->Unbind();
}

void scene::PBR::OnUpdate(float deltaTime)
{
    cameraController.OnUpdate(deltaTime);
}

void scene::PBR::OnMouseMovedEvent(double posX, double posY)
{
    cameraController.rotateCamera(posX, posY);
}

void scene::PBR::OnMouseScrolledEvent(double offsetX, double offsetY)
{
    cameraController.zoomCamera(offsetX, offsetY);
}

void scene::PBR::OnRender()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cameraController.getCamera().Sensitivity = 0.005f;
    renderer.Submit(cameraController.getCamera());

    shader->Bind();
    glm::mat4 view = cameraController.getViewMatrix();
    renderer.Submit(cameraController.getCamera());
    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    shader->SetUniformMat4f("projection", projection);
    shader->SetUniformMat4f("view", view);
    shader->SetUniform3f("camPos", cameraController.getCameraPos());

    // render rows*column number of spheres with varying metallic/roughness values scaled by rows and columns respectively
    glm::mat4 model = glm::mat4(1.0f);
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

void scene::PBR::OnImGuiRender()
{
}

void scene::PBR::OnEvent(int event)
{
    cameraController.processInput(event);
}
