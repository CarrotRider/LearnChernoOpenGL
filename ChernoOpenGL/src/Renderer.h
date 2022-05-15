#ifndef RENDERER_H
#define RENDERER_H

class VertexArray;
class IndexBuffer;
class Shader;


#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x,__FILE__,__LINE__))

void GLClearError();

bool GLLogCall(const char* func, const char* file, int line);


class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Clear(float r, float g, float b, float a) const;
    void Draw(const VertexArray& va, const IndexBuffer& ib,
        const Shader& shader) const;
};

#endif