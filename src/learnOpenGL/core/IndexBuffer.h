#pragma once

#include <vector>

class IndexBuffer
{
private:
	unsigned int m_RendererId = 0;
	unsigned int m_Count = 0;
public:
	IndexBuffer();
	IndexBuffer(const unsigned int* data, unsigned int count);
	IndexBuffer(std::vector<unsigned int> data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
};