/**
 * Grafika: Task 2a
 * Mar 28, 2019
 * 
 * Task: Create colored pentagon with shader
 * 
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <csignal>
#include <cstdlib>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
using namespace Jokowi;

#define DEBUG

int main() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Task 2a: Pentagon with shader", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // To make animation smoother
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        float vertices[] = {
            // x, y, r, g, b, a
            0.000000f, 0.000000f,   1.0f, 0.0f, 0.0f, 1.0f, // 0  
            0.000000f, 0.849841f,   0.8f, 0.5f, 0.8f, 1.0f, // 1
            0.809016f, 0.262056f,   0.0f, 0.0f, 1.0f, 1.0f, // 2
            0.500000f, -0.689000f,  0.0f, 0.8f, 0.3f, 1.0f, // 3
            -0.500000f, -0.689000f, 0.8f, 0.3f, 0.2f, 1.0f, // 4
            -0.809016f, 0.262056f,  0.3f, 0.5f, 0.8f, 1.0f  // 5
        };

        unsigned int indices[] = {
            1, 0, 2,
            2, 0, 3,
            3, 0, 4,
            4, 0, 5,
            5, 0, 1
        };

        // VertexArray
        Jokowi::VertexArray va;

        // VertexBuffer
        Jokowi::VertexBuffer vb(vertices, 6 * 6 * sizeof(float));

        Jokowi::VertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(4);
        va.addBuffer(vb, layout);

        // IndexBuffer
        Jokowi::IndexBuffer ib(indices, 15);

        // Shaders
        Jokowi::Shader shader("../res/shaders/basic.glsl");

        va.unbind();
        vb.unbind();
        ib.unbind();
        shader.unbind();

        // Renderer
        Jokowi::Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            renderer.clear(true);

            renderer.draw(va, ib, shader);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }


    glfwTerminate();
    return 0;
}
