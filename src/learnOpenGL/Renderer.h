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
    void Submit(Camera& camera);
    void RenderLight(Light& light, Shader& shader);
    void RenderObject(Model& model, Shader& shader);
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

private:
    void RenderMesh(Mesh& mesh, Shader& shader, glm::vec3 pos, glm::vec3 scale) const;
    void enableStencil();
    void disableStencil();
    void defaultStencil();
    SceneData m_SceneData;
    Shader selection;
};