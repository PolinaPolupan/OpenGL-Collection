#include "Renderer.h"
#include "Shader.h"
#include "Lights.h"
#include "Camera.h"
#include "Model.h"
#include "FileUtils.h"


void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGl Error] (" << error << ":) " << function <<
            " " << file << ":" << std::endl;
        return false;
    }
    return true;
}

Renderer::Renderer() : m_Selection(GetResourcePath("res\\shaders\\Light.shader"))
{
    
}

void Renderer::Clear()
{
    ClearColor();
    ClearBuffer();
    EnableDepthTesting();
    GLCall(glDisable(GL_CULL_FACE));
    DisableBlending();
}

void Renderer::ClearBuffer(GLbitfield mask)
{
    GLCall(glClear(mask));
}

void Renderer::ClearColor(const glm::vec4& color)
{
    GLCall(glClearColor(color.r, color.g, color.b, color.a));
}

void Renderer::EnableDepthTesting(GLenum func, GLboolean flag)
{
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glDepthFunc(func));
    GLCall(glDepthMask(flag));
}

void Renderer::DisableDepthTesting()
{
    GLCall(glDisable(GL_DEPTH_TEST));
}

void Renderer::EnableBlending()
{
    GLCall(glEnable(GL_BLEND));
}

void Renderer::EnableDepthWriting()
{
    GLCall(glDepthMask(GL_TRUE));
}

void Renderer::DisableDepthWriting()
{
    GLCall(glDepthMask(GL_FALSE));
}

void Renderer::DisableBlending()
{
    GLCall(glDisable(GL_BLEND));
}

void Renderer::SetBlendingFunction(GLenum sfactor, GLenum dfactor)
{
    GLCall(glBlendFunc(sfactor, dfactor));
}

void Renderer::SetTargetBlendingFunction(GLuint buf, GLenum sfactor, GLenum dfactor)
{
    GLCall(glBlendFunci(buf, sfactor, dfactor));
}

void Renderer::SetBlendingEquation(GLenum mode)
{
    GLCall(glBlendEquation(mode));
}

void Renderer::SetDepthFunction(GLenum func)
{
    GLCall(glDepthFunc(func));
}

void Renderer::ClearTargetBufferFv(GLenum buffer, GLint drawBuffer, const glm::vec4& value)
{
    GLCall(glClearBufferfv(buffer, drawBuffer, &value[0]));
}

void Renderer::Submit(Camera& camera)
{
    m_SceneData.projection = camera.GetProjectionMatrix();
    m_SceneData.view = camera.GetViewMatrix();
};


void Renderer::RenderLight(Light& light, Shader& shader)
{
    
    std::string name = "lights[" + std::to_string(light.Id()) + "].";

    shader.Bind();
    shader.SetUniform1i(name + "type", light.GetType());
    shader.SetUniform3f(name + "position", light.GetModel().position);
    shader.SetUniform3f(name + "direction", light.direction);
    shader.SetUniform3f(name + "color", light.color);
    shader.SetUniform1f(name + "cutOff", glm::cos(glm::radians(light.cutOff)));
    shader.SetUniform1f(name + "outerCutOff", glm::cos(glm::radians(light.outerCutOff)));
    shader.SetUniform1f(name + "constant", light.constant);
    shader.SetUniform1f(name + "linear", light.linear);
    shader.SetUniform1f(name + "quadratic", light.quadratic);
    shader.SetUniform1f(name + "intensity", light.GetIntensity());

    light.GetShader()->Bind();
    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, light.GetModel().position); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down;
    light.GetShader()->SetUniformMat4f("model", model);
    light.GetShader()->SetUniformMat4f("projection", m_SceneData.projection);
    light.GetShader()->SetUniformMat4f("view", m_SceneData.view);
    light.GetShader()->SetUniform3f("lightColor", light.color);
    light.GetShader()->Unbind();
    
    if (!light.GetModel().isHidden)
    {
        RenderObject(light.GetModel(), *light.GetShader());
    }
}

void Renderer::RenderObject(Model& model, Shader& shader) 
{
    DisableStencil();
    for (unsigned int i = 0; i < model.GetMeshes().size(); i++)
    {
            
        shader.Bind();
        shader.SetUniformMat4f("projection", m_SceneData.projection);
        shader.SetUniformMat4f("view", m_SceneData.view);
        RenderMesh(model.GetMeshes()[i], shader, model.position, model.scale);
        shader.Unbind();
    }
    /*if (model.isSelected) 
    {
        enableStencil();
        for (unsigned int i = 0; i < model.getMeshes().size(); i++)
        {

            selection.Bind();
            selection.SetUniformMat4f("projection", m_SceneData.projection);
            selection.SetUniformMat4f("view", m_SceneData.view);
            RenderMesh(model.getMeshes()[i], selection, model.position, model.scale);
            selection.Unbind();
        }  
    }
    defaultStencil();*/
    glClear(GL_STENCIL_BUFFER_BIT);
}

void Renderer::RenderMesh(Mesh& mesh, Shader& shader, glm::vec3 pos, glm::vec3 scale) const
{
    shader.Bind();
    glm::mat4 modelMat = glm::mat4(1.0f);
	
	std::string number;
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

	for (unsigned int i = 0; i < mesh.textures.size(); i++)
	{

		Texture::Type type = mesh.textures[i]->GetType();
		std::string name = mesh.textures[i]->GetTextureTypeName();

		switch (type)
		{
        case Texture::Type::Diffuse:
			number = std::to_string(diffuseNr++);
			break;

        case Texture::Type::Specular:
			number = std::to_string(specularNr++);
			break;

        case Texture::Type::Normal:
            number = std::to_string(normalNr++);
            break;

        case Texture::Type::Height:
            number = std::to_string(heightNr++);
            break;
		}

		
        mesh.textures[i]->Bind(i);

		shader.Bind();
        shader.SetUniform1i(("material." + name + number).c_str(), i);
	}
	
    shader.SetUniform3f("lightColor", glm::vec3(1.f));
	modelMat = glm::translate(modelMat, pos); // translate it down so it's at the center of the scene
	modelMat = glm::scale(modelMat, scale);	// it's a bit too big for our scene, so scale it down
	shader.SetUniformMat4f("model", modelMat);
    
	Draw(*mesh.GetVAO(), *mesh.GetIBO(), shader);
}

void Renderer::EnableStencil()
{
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
}

void Renderer::DisableStencil()
{
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
}

void Renderer::DefaultStencil()
{
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
 
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

    shader.Unbind();
    va.Unbind();
    ib.Unbind();
}
