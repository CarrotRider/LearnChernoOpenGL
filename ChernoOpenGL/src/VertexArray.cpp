#include "VertexArray.h"
#include <glad/glad.h>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::UnBind() const
{
	GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, 
	const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 
		sizeof(float) * 2, 0));
	// todo
	const auto& attribs = layout.VertexAttribs();
	int length = attribs.size();
	unsigned int offset = 0;
	for (int i = 0; i < length; i++)
	{
		const auto& element = attribs[i];
		GLCall(glVertexAttribPointer(i, element.count, element.type,
			element.normalized, layout.GetStride(), (const void*)offset));
		GLCall(glEnableVertexAttribArray(i));
		offset += element.count * VertexAttribElement::GetSizeOfType(element.type);
	}
}
