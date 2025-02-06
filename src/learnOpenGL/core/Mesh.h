#pragma once

#include <vector>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

class Texture;
class Shader;

class Mesh {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<Texture>> textures);
    std::shared_ptr<VertexArray>& GetVAO() { return m_VAO; }
    std::shared_ptr<VertexBuffer>& GetVBO() { return m_VBO; }
    std::shared_ptr<IndexBuffer>& GetIBO() { return m_IBO; }

public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<Texture>> textures;

private:
    std::shared_ptr<VertexArray> m_VAO;
    std::shared_ptr<VertexBuffer> m_VBO;
    std::shared_ptr<IndexBuffer> m_IBO;
};