#pragma once

#include <vector>
#include "Vertex.h"
#include <glad/glad.h>

class VertexBuffer
{
public:
    class Builder {
    public:
        friend class VertexBuffer;

        Builder();
        ~Builder();

        Builder& SetUsage(GLenum usage) { m_Usage = usage; return *this; }
        Builder& SetData(void* data, unsigned int size) {
            if (data) {
                if (m_Data) {
                    delete[] m_Data;
                }
                m_Data = new unsigned char[size];
                std::memcpy(m_Data, data, size);
            }
            m_Size = size;
            return *this;
        }

    private:
        GLenum m_Usage;
        void* m_Data;
        unsigned int m_Size;
    };

	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer(const std::vector<Vertex>& data, unsigned int size);
    VertexBuffer(const Builder& builder);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

    const unsigned int GetId() const { return m_RendererId; }
    void SetBufferAt(void* data, unsigned int size, GLintptr offset);

private:
	unsigned int m_RendererId;
};