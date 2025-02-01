#include "Framebuffers.h"

std::vector<double> calculateGaussian(int length, double weight)
{
    std::vector<double>Kernel(length * length);
    double sumTotal = 0;


    int kernelRadius = length / 2;
    double distance = 0;


    double calculatedEuler = 1.0 /
        (2.0 * 3.14 * weight * weight);


    for (int filterY = -kernelRadius; filterY <= kernelRadius; filterY++)
    {
        for (int filterX = -kernelRadius; filterX <= kernelRadius; filterX++)
        {
            distance = ((filterX * filterX) +
                (filterY * filterY)) /
                (2 * (weight * weight));

            int y = filterY + kernelRadius;
            int x = filterX + kernelRadius;
            int index = y * length + x;
            Kernel[index] = calculatedEuler * std::exp(-distance);


            sumTotal += Kernel[index];
        }
    }

    for (int y = 0; y < length; y++)
    {
        for (int x = 0; x < length; x++)
        {
            int index = y * length + x;
            Kernel[index] = Kernel[index] *
                (1.0 / sumTotal);
        }
    }

    return Kernel;
}

std::vector<double> calculateMedian(int length)
{
    std::vector<double>Kernel(length, 1);
    
    for (int i = 0; i < length; i++) {
        Kernel[i] /= length;
    }

    return Kernel;
}


scene::Framebuffers::Framebuffers():
	shader(GetResourcePath("res\\shaders\\5.1.framebuffers.vs")),
    screenShader(GetResourcePath("res\\shaders\\5.1.framebuffers_screen.vs")),
	cubeTexture(GetResourcePath("res\\textures\\wall.jpg"), Texture::Type::Diffuse),
    planeTexture(GetResourcePath("res\\textures\\wall.jpg"), Texture::Type::Diffuse)
{
    unsigned int planeIndices[] = { 0, 1, 2, 3, 4, 5 };

    unsigned int quadIndices[] = { 0, 1, 2, 3, 4, 5 };

    float planeVertices[] = {
        // positions          // texture Coords 
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };


    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    float cubeVertices[] = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int cubeIndices[] = {
        0, 1, 2, 3, 4, 5,
        6, 7, 8, 9, 10, 11,
        12, 13, 14, 15, 16, 17,
        18, 19, 20, 21, 22, 23,
        24, 25, 26, 27, 28, 29,
        30, 31, 32, 33, 34, 35
    };

    cubeVBO = std::make_shared<VertexBuffer>(cubeVertices, sizeof(cubeVertices));
    cubeIBO = std::make_shared <IndexBuffer>(cubeIndices, 36);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    cubeVAO.AddBuffer(*cubeVBO, layout);

    planeVBO = std::make_shared<VertexBuffer>(planeVertices, sizeof(planeVertices));
    planeIBO = std::make_shared<IndexBuffer>(planeIndices, 6);
    planeVAO.AddBuffer(*planeVBO, layout);

    quadVBO = std::make_shared<VertexBuffer>(quadVertices, sizeof(quadVertices));
    quadIBO = std::make_shared<IndexBuffer>(quadIndices, 6);
    VertexBufferLayout layout1;
    layout1.Push<float>(2);
    layout1.Push<float>(2);
    quadVAO.AddBuffer(*quadVBO, layout1);

    cubeTexture.Bind();
    planeTexture.Bind();

    shader.Bind();
    shader.SetUniform1i("texture1", 0);

    screenShader.Bind();
    screenShader.SetUniform1i("matrixSize", matrixSize);
    screenShader.SetUniform1i("screenTexture", 0);
    for (int i = 0; i < 9; i++)
    {
        screenShader.Bind();
        GLCall(screenShader.SetUniform1f("matrix" + std::to_string(i), matrix[i]));
    }

    // framebuffer configuration
    // -------------------------
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    // create a color attachment texture
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

scene::Framebuffers::~Framebuffers()
{
    cubeVAO.Unbind();
    cubeIBO->Unbind();
    
    planeVAO.Unbind();
    planeIBO->Unbind();

    cubeTexture.Unbind();
    planeTexture.Unbind();

    shader.Unbind();
    screenShader.Unbind();

    glDeleteRenderbuffers(1, &rbo);
    glDeleteFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glEnable(GL_DEPTH_TEST); // enable depth sceneing (is disabled for rendering screen-space quad)
}

void scene::Framebuffers::OnUpdate(float deltaTime)
{
    cameraController.OnUpdate(deltaTime);
}

void scene::Framebuffers::OnMouseMovedEvent(double posX, double posY)
{
    cameraController.RotateCamera(posX, posY);
}

void scene::Framebuffers::OnMouseScrolledEvent(double offsetX, double offsetY)
{
    cameraController.ZoomCamera(offsetX, offsetY);
}

void scene::Framebuffers::OnRender()
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glEnable(GL_DEPTH_TEST); // enable depth sceneing (is disabled for rendering screen-space quad)

    // make sure we clear the framebuffer's content
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer.Submit(cameraController.GetCamera());
    shader.Bind();
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = cameraController.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    shader.SetUniformMat4f("view", view);
    shader.SetUniformMat4f("projection", projection);
    // cubes
    cubeVAO.Bind();
    cubeTexture.Bind();
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    shader.SetUniformMat4f("model", model);
    renderer.Draw(cubeVAO, *cubeIBO, shader);
    shader.Bind();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    shader.SetUniformMat4f("model", model);
    renderer.Draw(cubeVAO, *cubeIBO, shader);
    // floor
    shader.Bind();
    planeVAO.Bind();
    cubeTexture.Bind();
    shader.SetUniformMat4f("model", glm::mat4(1.0f));
    renderer.Draw(planeVAO, *planeIBO, shader);
    glBindVertexArray(0);

    // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST); // disable depth scene so screen-space quad isn't discarded due to depth scene.
    // clear all relevant buffers
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT);

    screenShader.Bind();
    screenShader.SetUniform1i("matrixSize", matrixSize);
    for (int i = 0; i < 9; i++)
    {
        screenShader.Bind();
        screenShader.SetUniform1f("matrix" + std::to_string(i), matrix[i]);
    }
    quadVAO.Bind();
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
    renderer.Draw(quadVAO, *quadIBO, screenShader);
}

void scene::Framebuffers::OnImGuiRender()
{
    ImGui::SliderInt("Matrix size", &matrixSize, 0, 3000);
    if (ImGui::BeginTable("table_item_width", 3, ImGuiTableFlags_Borders))
    {
        ImGui::TableSetupColumn("small");
        ImGui::TableSetupColumn("half");
        ImGui::TableSetupColumn("right-align");
        ImGui::TableHeadersRow();

        for (int row = 0; row < 3; row++)
        {
            ImGui::TableNextRow();

            // Draw our contents
            ImGui::PushID(row);
            ImGui::TableSetColumnIndex(0);
            ImGui::SliderFloat(std::to_string(row * 3).c_str(), &matrix[row * 3], -10.0f, 10.0f);
            ImGui::TableSetColumnIndex(1);
            ImGui::SliderFloat(std::to_string(row * 3 + 1).c_str(), &matrix[row * 3 + 1], -10.0f, 10.0f);
            ImGui::TableSetColumnIndex(2);
            ImGui::SliderFloat(std::to_string(row * 3 + 2).c_str(), &matrix[row * 3 + 2], -10.0f, 10.0f); // No visible label since right-aligned
            ImGui::PopID();
        }
        ImGui::EndTable();
    }
    
    if (ImGui::TreeNode("Gaussian Blur"))
    {
        static float weight = 9.f;
        ImGui::SliderFloat("Weight", &weight, 0.1f, 10.f);
        if (ImGui::Button("Gaussian Blur")) {
            auto kernel = calculateGaussian(3, weight);
            for (int i = 0; i < 9; i++) {
                matrix[i] = kernel[i];
            }
        }
        ImGui::TreePop();
    }

    if (ImGui::Button("Median Blur")) {
        auto kernel = calculateMedian(9);
        for (int i = 0; i < 9; i++) {
            matrix[i] = kernel[i];
        }
    }
    if (ImGui::Button("Bottom Sobel")) {
        matrix[0] = -1;
        matrix[1] = -2;
        matrix[2] = -1;

        matrix[3] = 0;
        matrix[4] = 0;
        matrix[5] = 0;

        matrix[6] = 1;
        matrix[7] = 2;
        matrix[8] = 1;
    }
    if (ImGui::Button("Emboss")) {
        matrix[0] = -1;
        matrix[1] = -2;
        matrix[2] = 0;

        matrix[3] = -1;
        matrix[4] = 1;
        matrix[5] = 1;

        matrix[6] = 0;
        matrix[7] = 2;
        matrix[8] = 1;
    }
    if (ImGui::Button("Sharpen")) {
        matrix[0] = 0;
        matrix[1] = -1;
        matrix[2] = 0;

        matrix[3] = -1;
        matrix[4] = 5;
        matrix[5] = -1;

        matrix[6] = 0;
        matrix[7] = -1;
        matrix[8] = 0;
    }
}

void scene::Framebuffers::OnEvent(int event)
{
    cameraController.ProcessInput(event);
}

