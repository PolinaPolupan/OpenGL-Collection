#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererId));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(const std::vector<Vertex>& data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererId));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, &data[0], GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(const Builder& builder)
{
    GLCall(glGenBuffers(1, &m_RendererId));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, builder.m_Size, builder.m_Data, builder.m_Usage));
}

VertexBuffer::~VertexBuffer() 
{
    GLCall(glDeleteBuffers(1, &m_RendererId));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::SetBufferAt(void* data, unsigned int size, GLintptr offset)
{
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

VertexBuffer::Builder::Builder():
    m_Usage(GL_STATIC_DRAW),
    m_Size(0),
    m_Data(nullptr) {}

VertexBuffer::Builder::~Builder()
{
    if (m_Data) delete[] m_Data;
}

