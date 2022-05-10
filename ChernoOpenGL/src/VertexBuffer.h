#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class VertexBuffer
{
public:
	VertexBuffer(const void * data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;
private:
	unsigned int m_RendererID;
};

#endif // !VERTEX_BUFFER_H

