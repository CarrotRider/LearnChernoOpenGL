#include <iostream>
#include <glad/glad.h>
#include "Renderer.h"

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