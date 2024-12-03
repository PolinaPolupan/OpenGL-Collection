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
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

class Mesh {
public:
    // mesh data
    std::vector<CustomVertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    Mesh(std::vector<CustomVertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<Texture>> textures);
    std::shared_ptr<VertexArray>& getVAO() { return m_VAO; }
    std::shared_ptr<VertexBuffer>& getVBO() { return m_VBO; }
    std::shared_ptr<IndexBuffer>& getIBO() { return m_IBO; }
private:
    //  render data
    std::shared_ptr<VertexArray> m_VAO;
    std::shared_ptr<VertexBuffer> m_VBO;
    std::shared_ptr<IndexBuffer> m_IBO;
};