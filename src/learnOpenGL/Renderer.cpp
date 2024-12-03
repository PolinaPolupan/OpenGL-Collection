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

Renderer::Renderer() : selection(GetResourcePath("res\\shaders\\Light.shader"))
{
    
}

void Renderer::Clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Submit(Camera& camera)
{
    m_SceneData.projection = camera.GetProjectionMatrix();
    m_SceneData.view = camera.GetViewMatrix();
};


void Renderer::RenderLight(Light& light, Shader& shader)
{
    
    std::string name = "lights[" + std::to_string(light.id()) + "].";

    shader.Bind();
    shader.SetUniform1i(name + "type", light.getType());
    shader.SetUniform3f(name + "position", light.getModel().position);
    shader.SetUniform3f(name + "direction", light.direction);
    shader.SetUniform3f(name + "color", light.color);
    shader.SetUniform1f(name + "cutOff", glm::cos(glm::radians(light.cutOff)));
    shader.SetUniform1f(name + "outerCutOff", glm::cos(glm::radians(light.outerCutOff)));
    shader.SetUniform1f(name + "constant", light.constant);
    shader.SetUniform1f(name + "linear", light.linear);
    shader.SetUniform1f(name + "quadratic", light.quadratic);
    shader.SetUniform1f(name + "intensity", light.getIntensity());

    light.getShader()->Bind();
    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, light.getModel().position); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down;
    light.getShader()->SetUniformMat4f("model", model);
    light.getShader()->SetUniformMat4f("projection", m_SceneData.projection);
    light.getShader()->SetUniformMat4f("view", m_SceneData.view);
    light.getShader()->SetUniform3f("lightColor", light.color);
    light.getShader()->Unbind();
    
    if (!light.getModel().isHidden)
    {
        RenderObject(light.getModel(), *light.getShader());
    }
}

void Renderer::RenderObject(Model& model, Shader& shader) 
{
    disableStencil();
    for (unsigned int i = 0; i < model.getMeshes().size(); i++)
    {
            
        shader.Bind();
        shader.SetUniformMat4f("projection", m_SceneData.projection);
        shader.SetUniformMat4f("view", m_SceneData.view);
        RenderMesh(model.getMeshes()[i], shader, model.position, model.scale);
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

		TextureType type = mesh.textures[i]->getType();
		std::string name = mesh.textures[i]->getTextureTypeName();

		switch (type)
		{
		case Diffuse:
			number = std::to_string(diffuseNr++);
			break;

		case Specular:
			number = std::to_string(specularNr++);
			break;

        case Normal:
            number = std::to_string(normalNr++);
            break;

        case Height:
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
    
	Draw(*mesh.getVAO(), *mesh.getIBO(), shader);
}

void Renderer::enableStencil()
{
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
}

void Renderer::disableStencil()
{
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
}

void Renderer::defaultStencil()
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
