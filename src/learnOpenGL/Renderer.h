#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "SceneData.h"
#include "Shader.h"

class Mesh;
class Model;
class Light;
class Shader;
class Camera;

#define ASSERT(x) if (!x) __debugbreak();
#define GLCall(x)  GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    Renderer();
    void Clear();
    void ClearBuffer(GLbitfield mask = (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
    void ClearColor(const glm::vec4& color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
    void EnableDepthTesting(GLenum func = GL_LESS, GLboolean flag = GL_TRUE);
    void DisableDepthTesting();
    void EnableBlending();
    void EnableDepthWriting();
    void DisableDepthWriting();
    void DisableBlending();
    void SetBlendingFunction(GLenum sfactor, GLenum dfactor);
    void SetTargetBlendingFunction(GLuint buf, GLenum sfactor = GL_ONE, GLenum dfactor = GL_ZERO);
    void SetBlendingEquation(GLenum mode);
    void SetDepthFunction(GLenum func);
    void ClearTargetBufferFv(GLenum buffer, GLint drawBuffer, const glm::vec4& value);
    void Submit(Camera& camera);
    void RenderLight(Light& light, Shader& shader);
    void RenderObject(Model& model, Shader& shader);
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

private:
    void RenderMesh(Mesh& mesh, Shader& shader, glm::vec3 pos, glm::vec3 scale) const;
    void EnableStencil();
    void DisableStencil();
    void DefaultStencil();
    SceneData m_SceneData;
    Shader m_Selection;
};