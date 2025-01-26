#pragma once

#include <vector>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

class Texture;
class Shader;
#define MAX_BONE_INFLUENCE 4

struct CustomVertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

class Mesh {
public:
    Mesh(std::vector<CustomVertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<Texture>> textures);
    std::shared_ptr<VertexArray>& GetVAO() { return m_VAO; }
    std::shared_ptr<VertexBuffer>& GetVBO() { return m_VBO; }
    std::shared_ptr<IndexBuffer>& GetIBO() { return m_IBO; }

public:
    std::vector<CustomVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<Texture>> textures;

private:
    std::shared_ptr<VertexArray> m_VAO;
    std::shared_ptr<VertexBuffer> m_VBO;
    std::shared_ptr<IndexBuffer> m_IBO;
};