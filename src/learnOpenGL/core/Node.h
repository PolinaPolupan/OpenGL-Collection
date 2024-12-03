#pragma once

class Node
{
public:
	Node(unsigned int id)
		: m_id(id) {};

	void destroy()
	{
		m_isActive = false;
	}
	inline bool isActive() const { return m_isActive; }

	inline unsigned int id() const { return m_id; }

protected:	
	unsigned int m_id = 0;
	bool m_isActive = true;
};
