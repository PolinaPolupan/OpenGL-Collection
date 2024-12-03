#include "Mesh.h"
#include "Renderer.h"
#include "core\Texture.h"
#include "Shader.h"
#include "Vertex.h"

Mesh::Mesh(std::vector<CustomVertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<Texture>> textures) :
	vertices(vertices),
	indices(indices),
	textures(textures)
{
	m_VAO = std::make_unique<VertexArray>();
	m_VAO->Bind();

	m_VBO = std::make_unique<VertexBuffer>(&vertices[0], vertices.size() * sizeof(CustomVertex));
	m_VBO->Bind();

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);
	layout.Push<float>(3);
	layout.Push<float>(3);
	m_VAO->AddBuffer(*m_VBO, layout);

	m_IBO = std::make_unique<IndexBuffer>(indices, indices.size());
	m_IBO->Bind();

	m_VAO->Unbind();
	m_VBO->Unbind();
	m_IBO->Unbind();
}


