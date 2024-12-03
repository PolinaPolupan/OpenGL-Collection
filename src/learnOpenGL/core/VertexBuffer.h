#pragma once

#include <vector>
#include "Vertex.h"

class VertexBuffer
{
private:
	unsigned int m_RendererId;
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer(std::vector<Vertex> data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};