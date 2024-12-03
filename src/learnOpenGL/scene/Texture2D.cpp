#include "Texture2D.h"

scene::Texture2D::Texture2D()
	: m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0) 
{
    float positions[] = {
       -100.f, -100.f, 0.f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        100.f, -100.f, 0.f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        100.f, 100.f,  0.f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
       -100.f, 100.f,  0.f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    m_Shader = std::make_unique<Shader>(GetResourcePath("res/shaders/Basic.shader"));
    m_VAO = std::make_unique<VertexArray>();
    m_Texture = std::make_unique<Texture>(GetResourcePath("res/textures/vader.png"), TextureType::Diffuse);

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    
    m_VBO = std::make_unique<VertexBuffer>(positions, sizeof(positions));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    m_VAO->AddBuffer(*m_VBO, layout);
    m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

    m_Proj = glm::ortho(0.f, 640.f, 0.f, 480.f, -1.f, 1.f);
    m_View = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f));
    m_Shader->Bind();
    m_Texture->Bind();
    m_Shader->SetUniform1i("u_Texture", 0);

    m_VAO->Unbind();
    m_VBO->Unbind();
    m_IndexBuffer->Unbind();
    m_Shader->Unbind();
}

scene::Texture2D::~Texture2D()
{
    m_Texture->Unbind();
    m_VAO->Unbind();
    m_VBO->Unbind();
    m_IndexBuffer->Unbind();
    m_Shader->Unbind();
}

void scene::Texture2D::OnUpdate(float deltaTime)
{
}

void scene::Texture2D::OnRender()
{
	GLCall(glClearColor(0.f, 0.f, 0.f, 1.f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
    
    Renderer renderer;
 
    m_Texture->Bind();
    m_VAO->Bind();
    {
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.0f, 0.5f, 0.0f));
        trans = glm::rotate(trans, -1.f * (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(abs(glm::sin((float)glfwGetTime())), abs(glm::sin((float)glfwGetTime())), 1.0f));
        glm::mat4 model = glm::translate(glm::mat4(1.f), m_TranslationA);
        glm::mat4 mvp = m_Proj * m_View * model;
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        m_Shader->SetUniformMat4f("transform", trans);
        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        m_Shader->Unbind();
    }
    {
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.2f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        
        glm::mat4 model = glm::translate(glm::mat4(1.f), m_TranslationB);
        glm::mat4 mvp = m_Proj * m_View * model;
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        m_Shader->SetUniformMat4f("transform", trans);
        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        m_Shader->Unbind();
    }
}


void scene::Texture2D::OnImGuiRender()
{
    ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.f);
    ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.f);
}
