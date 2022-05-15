#include <iostream>
#include <glad/glad.h>
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* func, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error]: " << error << std::endl;
        std::cout << "      Function: " << func << std::endl;
        std::cout << "          File: " << file << std::endl;
        std::cout << "          Line: " << line << std::endl;
        return false;
    }
    return true;
}

Renderer::Renderer()
{

}
Renderer::~Renderer()
{

}

void Renderer::Clear(float r, float g, float b, float a) const
{
    GLCall(glClearColor(r, g, b, a));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib,
    const Shader& shader) const
{
    va.Bind();
    ib.Bind();
    shader.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), 
        GL_UNSIGNED_INT, nullptr));
}