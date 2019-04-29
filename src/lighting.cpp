/**
 * Grafika: Exploring OpenGL - learnopengl.com
 * Apr 2, 2019
 * 
 * Task: None
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
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
using namespace Jokowi;

#define DEBUG

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// stores how much we're seeing of either texture
float mixValue = 0.2f;

float angleX = 0.35f;
float angleY = 0.25f;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

void processInput(GLFWwindow *window) {
    // ESC key pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Up key pressed
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        mixValue += 0.01f; // change this value accordingly (might be too slow or too fast based on system hardware)
        if(mixValue >= 1.0f)
            mixValue = 1.0f;
    }

    // Down key pressed
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        mixValue -= 0.01f; // change this value accordingly (might be too slow or too fast based on system hardware)
        if (mixValue <= 0.0f)
            mixValue = 0.0f;
    }

    float speed = 2.5f * deltaTime;; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        angleX += speed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        angleX -= speed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        angleY -= speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        angleY += speed;
}

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
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Exploring OpenGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // To make animation smoother
    // glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        glEnable(GL_DEPTH_TEST);

        float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        // VertexArray
        Jokowi::VertexArray cubeVAO;

        // VertexBuffer
        Jokowi::VertexBuffer vb(vertices, 6 * 6 * 8 * sizeof(float));

        Jokowi::VertexBufferLayout layout;
        layout.push<float>(3);
        layout.push<float>(3);
        layout.push<float>(2);
        cubeVAO.addBuffer(vb, layout);

        Jokowi::VertexArray lightVAO;
        lightVAO.addBuffer(vb, layout);

        // Shaders
        Jokowi::Shader shader("../res/shaders/lighting.glsl");
        shader.setUniform3f("objectColor", 1.0f, 0.5f, 0.31f);
        shader.setUniform3f("lightColor",  1.0f, 1.0f, 1.0f);
        shader.setUniformVec3f("lightPos", lightPos);

        Jokowi::Shader lampShader("../res/shaders/lamp.glsl");


        cubeVAO.unbind();
        lightVAO.unbind();
        vb.unbind();
        shader.unbind();
        lampShader.unbind();


        // Renderer
        Jokowi::Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame; 
            processInput(window);

            /* Render here */
            renderer.clear(false);
            
            shader.bind();
            // shader.setUniform3f("objectColor", 1.0f, 0.5f, 0.31f);
            // shader.setUniform3f("lightColor",  1.0f, 1.0f, 1.0f);
            shader.setUniformVec3f("light.position", lightPos);
            // light properties
            glm::vec3 lightColor;
            lightColor.x = sin(glfwGetTime() * 2.0f);
            lightColor.y = sin(glfwGetTime() * 0.7f);
            lightColor.z = sin(glfwGetTime() * 1.3f);
            glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // decrease the influence
            glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
            shader.setUniformVec3f("light.ambient", ambientColor);
            shader.setUniformVec3f("light.diffuse", diffuseColor);
            shader.setUniform3f("light.specular", 1.0f, 1.0f, 1.0f);
            
            float radius = 10.0f;
            float camY = radius * sin(angleX);
            float camX = radius * cos(angleX) * sin(angleY);
            float camZ = radius * cos(angleX) * cos(angleY);
            glm::mat4 view;
            view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));  
            shader.setUniformVec3f("viewPos", glm::vec3(camX, camY, camZ));
            shader.setUniformMat4f("view", view);

            // material properties
            shader.setUniform3f("material.ambient", 1.0f, 0.5f, 0.31f);
            shader.setUniform3f("material.diffuse", 1.0f, 0.5f, 0.31f);
            shader.setUniform3f("material.specular", 0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
            shader.setUniform1f("material.shininess", 32.0f);
            

            glm::mat4 projection;
            projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            shader.setUniformMat4f("projection", projection);

            glm::mat4 model = glm::mat4(1.0f);
            shader.setUniformMat4f("model", model);

            // renderer.draw(cubeVAO, ib, shader);
            cubeVAO.bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);
            
            // Lamp object
            lampShader.bind();
            lampShader.setUniformMat4f("projection", projection);
            lampShader.setUniformMat4f("view", view);
            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
            lampShader.setUniformMat4f("model", model);

            // renderer.draw(lightVAO, ib, lampShader);
            lightVAO.bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }


    glfwTerminate();
    return 0;
}
