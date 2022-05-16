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

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 960, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(2);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float positions[]
    {
         250.0f,  540.0f, 0.0f, 0.0f,
         450.0f,  540.0f, 1.0f, 0.0f,
         450.0f,  740.0f, 1.0f, 1.0f,
         250.0f,  740.0f, 0.0f, 1.0f
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

        glm::mat4x4 proj = glm::ortho(0.0f, 1080.0f, 0.0f, 960.0f, -1.0f, 1.0f);

        vbo.UnBind();
        ibo.UnBind();
        shader.UnBind();

        Texture texture("res/textures/carrot.png");
        texture.Bind();

        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;

        bool show_demo_window = true;
        glm::vec3 trans = glm::vec3(0, 0, 0);
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            renderer.Clear(0.2f, 0.3f, 0.3f, 1.0f);
            shader.Bind();
            glm::mat4x4 model = glm::translate(glm::mat4(1.0f), trans);
            glm::mat4 mvp = proj * model;
            shader.SetUniform("u_MVP", mvp);
            shader.SetUniform("uTex", 0);
            renderer.Draw(va, ibo, shader);

            r += increment;
            if (r > 1)
                r = 0.0f;

            ImGui::SliderFloat3("Translation", &trans.x, -500.0f, 500.0f);

            /*ImGui::ShowDemoWindow(&show_demo_window);*/

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
            /* Poll for and process events */
            glfwPollEvents();
        }
     
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}