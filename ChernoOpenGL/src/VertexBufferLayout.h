#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#include <vector>
#include "Renderer.h"
#include <glad/glad.h>



struct VertexAttribElement
{
	unsigned int	type;
	unsigned int	count;
	unsigned char	normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return sizeof(float);
		case GL_UNSIGNED_INT:	return sizeof(unsigned int);
		case GL_UNSIGNED_BYTE:	return sizeof(unsigned char);
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout();
	~VertexBufferLayout();

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_VertexAttribs.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexAttribElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_VertexAttribs.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexAttribElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_VertexAttribs.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexAttribElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexAttribElement>&
		VertexAttribs() const { return m_VertexAttribs; }
	inline int GetStride() const { return m_Stride; }
private:
	std::vector<VertexAttribElement> m_VertexAttribs;
	unsigned int m_Stride;
};

#endif // !VERTEX_BUFFER_LAYOUT_H

