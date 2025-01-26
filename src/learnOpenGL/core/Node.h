#pragma once

class Node
{
public:
	Node(unsigned int id): m_Id(id), m_IsActive(true) {}

	void Destroy() { m_IsActive = false; }
	inline bool IsActive() const { return m_IsActive; }

	inline unsigned int Id() const { return m_Id; }

protected:	
	unsigned int m_Id;
	bool m_IsActive;
};
