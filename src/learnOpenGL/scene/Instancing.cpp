#include "Instancing.h"

scene::Instancing::Instancing()
{
    mode = Mode::QUADS;

    int index = 0;
    int offset = 0.1f;
    for (int y = -10; y < 10; y += 2)
    {
        for (int x = -10; x < 10; x += 2)
        {
            glm::vec2 translation;
            translation.x = (float)x / 10.0f + offset;
            translation.y = (float)y / 10.0f + offset;
            translations.push_back(translation);
        }
    }

    instanceShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\Instancing.shader"));
    asteroidsShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\InstancingAsteriods.shader"));
    planetShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\Planet.shader"));

    instanceVBO = std::make_shared<VertexBuffer>(&translations[0], sizeof(glm::vec2) * 100);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float quadVertices[] = {
        // positions     // colors
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
         0.05f,  0.05f,  0.0f, 1.0f, 1.0f
    };

    quadVAO = std::make_shared<VertexArray>();
    quadVBO = std::make_shared<VertexBuffer>(quadVertices, sizeof(quadVertices));

    quadVBO->Bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    // also set instance data
    glEnableVertexAttribArray(2);
    instanceVBO->Bind();
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.

    rock = std::make_shared<Model>(GetResourcePath("res\\objects\\rock\\rock.obj"));
    rock->LoadModel(GetResourcePath("res\\objects\\rock\\rock.obj"));
    planet = std::make_shared<Model>(GetResourcePath("res\\objects\\planet\\planet.obj"));
    planet->LoadModel(GetResourcePath("res\\objects\\planet\\planet.obj"));
}

scene::Instancing::~Instancing()
{
}

void scene::Instancing::OnUpdate(float deltaTime)
{
	cameraController.OnUpdate(deltaTime);
}

void scene::Instancing::OnMouseMovedEvent(double posX, double posY)
{
	cameraController.RotateCamera(posX, posY);
}

void scene::Instancing::OnMouseScrolledEvent(double offsetX, double offsetY)
{
}

void scene::Instancing::OnRender()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch (mode) {
    case QUADS: { OnRenderQuads(); break; }
    case ASTEROIDS: { OnRenderAsteroids(); break; }
    }
}

void scene::Instancing::OnImGuiRender()
{
    if (ImGui::SliderInt("amount", &amount, 100, 1000000) && mode == Mode::ASTEROIDS) {
        reloadAsteroids();
    }

    if (ImGui::SliderFloat("radius", &radius, 10, 100) && mode == Mode::ASTEROIDS) {
        reloadAsteroids();
    }

    if (ImGui::SliderFloat("offset", &offset, 10, 100) && mode == Mode::ASTEROIDS) {
        reloadAsteroids();
    }

    if (ImGui::Button("quads")) {
        mode = Mode::QUADS;
    }
    if (ImGui::Button("asteriods")) {

        reloadAsteroids();

        mode = Mode::ASTEROIDS;
    }
}

void scene::Instancing::OnEvent(int event)
{
	cameraController.ProcessInput(event);
}

void scene::Instancing::OnRenderQuads()
{
    quadVAO->Bind();
    instanceShader->Bind();
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100); // 100 triangles of 6 vertices each

    quadVAO->Unbind();
    instanceShader->Unbind();
}

void scene::Instancing::initAsteroidModelMatrices()
{
    modelMatrices.clear();
    srand(0); // initialize random seed	
    
    for (unsigned int i = 0; i < amount; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = rand() % 360;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.4f; // keep height of field smaller compared to width of x and z
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));

        // 2. scale: scale between 0.05 and 0.25f
        float scale = (rand() % 20) / 100.0f + 0.05;
        model = glm::scale(model, glm::vec3(scale));

        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        float rotAngle = (rand() % 360);
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

        // 4. now add to list of matrices
        modelMatrices.push_back(model);
    }
}

void scene::Instancing::reloadAsteroids()
{
    glDeleteBuffers(1, &buffer);
    initAsteroidModelMatrices();

    // vertex buffer object
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

    for (unsigned int i = 0; i < rock->GetMeshes().size(); i++)
    {
        std::shared_ptr<VertexArray> VAO = (*rock)[i].GetVAO();
        VAO->Bind();
        // vertex attributes
        std::size_t vec4Size = sizeof(glm::vec4);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
    }
}

void scene::Instancing::OnRenderAsteroids()
{
    renderer.Submit(cameraController.GetCamera());
    // configure transformation matrices
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
    glm::mat4 view = cameraController.GetViewMatrix();
    asteroidsShader->Bind();
    asteroidsShader->SetUniformMat4f("projection", projection);
    asteroidsShader->SetUniformMat4f("view", view);
    planetShader->Bind();
    planetShader->SetUniformMat4f("projection", projection);
    planetShader->SetUniformMat4f("view", view);

    // draw planet
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
    model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
    planetShader->SetUniformMat4f("model", model);
    renderer.RenderObject(*planet, *planetShader);

    // draw meteorites
    asteroidsShader->Bind();
    asteroidsShader->SetUniform1i("texture_diffuse1", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, rock->GetTexturesLoaded()["rock.png"]->GetId()); // note: we also made the textures_loaded vector public (instead of private) from the model class.
    for (unsigned int i = 0; i < rock->GetMeshes().size(); i++)
    {
        (*rock)[i].GetVAO()->Bind();
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>((*rock)[i].indices.size()), GL_UNSIGNED_INT, 0, amount);
        glBindVertexArray(0);
    }
}
