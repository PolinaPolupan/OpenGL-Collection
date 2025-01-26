#include "AdvancedGLSL.h"

#include <glm/gtc/type_ptr.hpp>


scene::AdvancedGLSL::AdvancedGLSL():
	shaderBlue(GetResourcePath("res/shaders/ShaderBlue.shader")),
	shaderGreen(GetResourcePath("res/shaders/ShaderGreen.shader")),
	shaderRed(GetResourcePath("res/shaders/ShaderRed.shader")),
	shaderYellow(GetResourcePath("res/shaders/ShaderYellow.shader"))
{
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float cubeVertices[] = {
        // positions         
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
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
    cubeIBO = std::make_shared<IndexBuffer>(cubeIndices, 36);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    cubeVAO.AddBuffer(*cubeVBO, layout);

    // configure a uniform buffer object
   // ---------------------------------
   // first. We get the relevant block indices
    uniformBlockIndexRed = glGetUniformBlockIndex(shaderRed.GetId(), "Matrices");
    uniformBlockIndexGreen = glGetUniformBlockIndex(shaderGreen.GetId(), "Matrices");
    uniformBlockIndexBlue = glGetUniformBlockIndex(shaderBlue.GetId(), "Matrices");
    uniformBlockIndexYellow = glGetUniformBlockIndex(shaderYellow.GetId(), "Matrices");
    // then we link each shader's uniform block to this uniform binding point
    glUniformBlockBinding(shaderRed.GetId(), uniformBlockIndexRed, 0);
    glUniformBlockBinding(shaderGreen.GetId(), uniformBlockIndexGreen, 0);
    glUniformBlockBinding(shaderBlue.GetId(), uniformBlockIndexBlue, 0);
    glUniformBlockBinding(shaderYellow.GetId(), uniformBlockIndexYellow, 0);
    // Now actually create the buffer
    glGenBuffers(1, &uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    // define the range of the buffer that links to a uniform binding point
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));

    // store the projection matrix (we only do this once now) (note: we're not using zoom anymore by changing the FoV)
    projection = glm::perspective(45.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

scene::AdvancedGLSL::~AdvancedGLSL()
{
    cubeVAO.Unbind();
    cubeIBO->Unbind();
    cubeVBO->Unbind();
	shaderBlue.Unbind();
	shaderGreen.Unbind();
	shaderRed.Unbind();
	shaderYellow.Unbind();
}

void scene::AdvancedGLSL::OnUpdate(float deltaTime)
{
    cameraController.OnUpdate(deltaTime);
}

void scene::AdvancedGLSL::OnMouseMovedEvent(double posX, double posY)
{
    cameraController.RotateCamera(posX, posY);
}

void scene::AdvancedGLSL::OnMouseScrolledEvent(double offsetX, double offsetY)
{
    cameraController.ZoomCamera(offsetX, offsetY);
}

void scene::AdvancedGLSL::OnRender()
{
    // render
        // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the view and projection matrix in the uniform block - we only have to do this once per loop iteration.
    glm::mat4 view = cameraController.GetViewMatrix();
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // draw 4 cubes 
    // RED
    cubeVAO.Bind();
    shaderRed.Bind();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-0.75f, 0.75f, 0.0f)); // move top-left
    shaderRed.SetUniformMat4f("model", model);
    renderer.Draw(cubeVAO, *cubeIBO, shaderRed);
    // GREEN
    shaderGreen.Bind();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.75f, 0.75f, 0.0f)); // move top-right
    shaderGreen.SetUniformMat4f("model", model);
    renderer.Draw(cubeVAO, *cubeIBO, shaderGreen);
    // YELLOW
    shaderYellow.Bind();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-0.75f, -0.75f, 0.0f)); // move bottom-left
    shaderYellow.SetUniformMat4f("model", model);
    renderer.Draw(cubeVAO, *cubeIBO, shaderYellow);
    // BLUE
    shaderBlue.Bind();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.75f, -0.75f, 0.0f)); // move bottom-right
    shaderBlue.SetUniformMat4f("model", model);
    renderer.Draw(cubeVAO, *cubeIBO, shaderBlue);
}

void scene::AdvancedGLSL::OnImGuiRender()
{
}

void scene::AdvancedGLSL::OnEvent(int event)
{
    cameraController.ProcessInput(event);
}
