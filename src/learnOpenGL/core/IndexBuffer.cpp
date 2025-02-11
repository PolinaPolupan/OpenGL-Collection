#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer():
    m_RendererId(0),
    m_Count(0) {}

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count):
    m_RendererId(0),
    m_Count(count)
{
    GLCall(glGenBuffers(1, &m_RendererId));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::IndexBuffer(std::vector<unsigned int> data, unsigned int count): 
    IndexBuffer(&data[0], count) {}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererId));
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}