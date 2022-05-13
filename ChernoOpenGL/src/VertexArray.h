#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

class VertexBuffer;
class VertexBufferLayout;

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void UnBind() const;

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

private:
	unsigned int m_RendererID;
};



#endif // !VERTEX_ARRAY_H

