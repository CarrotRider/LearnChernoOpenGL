#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(2);

    // glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float positions[]
    {
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
    };

    unsigned int index[]
    {
        0, 1, 2,
        2, 3, 0
    };

    {
        VertexArray va;
        VertexBuffer vbo(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vbo, layout);
        va.UnBind();

        IndexBuffer ibo(index, 6);

        Shader shader("res/shaders/basic.shader");
        shader.Bind();

        vbo.UnBind();
        ibo.UnBind();
        shader.UnBind();

        Texture texture("res/textures/carrot.png");
        texture.Bind();

        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear(0.2f, 0.3f, 0.3f, 1.0f);
            shader.Bind();
            //shader.SetUniform("uColor", r, 0.0f, 0.0f, 1.0f);
            shader.SetUniform("uTex", 0);
            renderer.Draw(va, ibo, shader);

            r += increment;
            if (r > 1)
                r = 0.0f;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
            /* Poll for and process events */
            glfwPollEvents();
        }
     
    }
    glfwTerminate();
    return 0;
}