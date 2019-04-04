/**
 * Grafika: Task 1
 * Mar 20, 2019
 * 
 * Task: Green pentagon
 * 
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Task 1: Green Pentagon", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_POLYGON);
        glColor3d(0.0f, 1.0f, 0.0f);
        glVertex2f(-0.5f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, 0.0f);
        glVertex2f(0.3f, -0.5f);
        glVertex2f(-0.3f, -0.5f);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
