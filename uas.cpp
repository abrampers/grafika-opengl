#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Maruf/shader.h>
#include <Maruf/camera.h>
#include <Maruf/model.h>
#include <Jokowi/Shader.h>
#include <Jokowi/Vertex.h>
#include <Jokowi/VertexArray.h>
#include <Jokowi/VertexBuffer.h>
#include <Jokowi/VertexBufferLayout.h>
#include <Jokowi/IndexBuffer.h>
#include <Jokowi/Texture.h>
#include <Jokowi/Particle.h>

#include <iostream>
#include <vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 1.5f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPos(10.0f, 10.0f, 2.0f);

int random(int min, int max) {
    static bool first = true;
    if (first) {  
        srand( time(NULL) ); //seeding for the first time only!
        first = false;
    }
    return min + rand() % (( max + 1 ) - min);
}

int main() {
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "UAS Computer Graphics: Jeep with rain", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    Shader ourShader("../res/shaders/1.model_loading.vs", "../res/shaders/1.model_loading.fs");
    ourShader.use();
    ourShader.setInt("material.diffuse", 0);
    ourShader.setInt("material.specular", 1);

    Jokowi::Shader lampShader("../res/shaders/lamp.glsl");
    Jokowi::VertexArray lightVAO;

    // VertexBuffer
    Jokowi::VertexBuffer vb(vertices, 6 * 6 * 3 * sizeof(float));

    Jokowi::VertexBufferLayout layout;
    layout.push<float>(3);
    lightVAO.addBuffer(vb, layout);

    // Lamp position
    glm::mat4 lampModel = glm::mat4(1.0f);
    lampModel = glm::translate(lampModel, lightPos);
    lampModel = glm::scale(lampModel, glm::vec3(0.2f)); // a smaller cube
    lampShader.bind();
    lampShader.setUniformMat4f("model", lampModel);

    // load models
    Model ourModel("../res/models/jeep/Jeep_Renegade_2016.obj");

    // Raindrop
    float raindrop_vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    };

    Jokowi::VertexArray raindrop_vao;
    Jokowi::VertexBuffer raindrop_vb(raindrop_vertices, 6 * 5 * sizeof(float));

    Jokowi::VertexBufferLayout raindrop_layout;
    raindrop_layout.push<float>(3);
    raindrop_layout.push<float>(2);
    raindrop_vao.addBuffer(raindrop_vb, raindrop_layout);

    Jokowi::Shader raindrop_shader("../res/shaders/raindrop.glsl");
    raindrop_shader.bind();
    
    Jokowi::Texture raindrop_texture("../res/textures/raindrop.png");
    raindrop_texture.bind(0);
    raindrop_shader.setUniform1i("raindrop_texture", 0);

    glm::vec3 neg_y(0.0f, -5.0f, 0.0f);

    std::vector<Jokowi::Particle> raindrops;
    int num_raindrops = 10000;
    for(int i = 0; i < num_raindrops; i++) {
        float pos_x = (float) (rand() % 200) / 10 - 10;
        float pos_y = (float) (rand() % 100) / 10 + 10;
        float pos_z = (float) (rand() % 200) / 10 - 10;
        Jokowi::Particle raindrop(glm::vec3(pos_x, pos_y, pos_z), neg_y);
        raindrops.push_back(raindrop);
    }

    float scale = 0.01f;
    glm::mat4 scale_matrix(1.0f);
    scale_matrix = glm::scale(scale_matrix, glm::vec3(scale, scale, scale));
    raindrop_shader.bind();
    raindrop_shader.setUniformMat4f("scale", scale_matrix);

    // Smoke
    float smoke_vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    };

    Jokowi::VertexArray smoke_vao;
    Jokowi::VertexBuffer smoke_vb(smoke_vertices, 6 * 5 * sizeof(float));

    Jokowi::VertexBufferLayout smoke_layout;
    smoke_layout.push<float>(3);
    smoke_layout.push<float>(2);
    smoke_vao.addBuffer(smoke_vb, smoke_layout);

    Jokowi::Shader smoke_shader("../res/shaders/smoke.glsl");
    smoke_shader.bind();
    Jokowi::Texture smoke_texture("../res/textures/smoke.png");
    smoke_texture.bind(0);
    smoke_shader.setUniform1i("smoke_texture", 0);

    glm::vec3 neg_z(0.0f, 0.0f, -0.1f);

    std::vector<Jokowi::Particle> smokes;
    int num_smokes = 100;
    for(int i = 0; i < num_smokes; i++) {
        float pos_x = (float) random(42, 50) / 100;
        float pos_y = (float) random(53, 57) / 100;
        float pos_z = (float) random(-250, -210) / 100;
        Jokowi::Particle smoke(glm::vec3(pos_x, pos_y, pos_z), neg_z);
        smokes.push_back(smoke);
    }
    
    smoke_shader.bind();
    smoke_shader.setUniformMat4f("scale", scale_matrix);

    Jokowi::Renderer renderer;

    // render loop
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Uniforms
        ourShader.use();
        ourShader.setVec3("light.position", lightPos);
        ourShader.setVec3("viewPos", camera.Position);

        // light properties
        ourShader.setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
        ourShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        ourShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        // material properties
        ourShader.setFloat("material.shininess", 64.0f);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);

        // Lamp object
        lampShader.bind();
        lampShader.setUniformMat4f("projection", projection);
        lampShader.setUniformMat4f("view", view);

        renderer.draw(lightVAO, 36, lampShader);

        // Raindrop
        raindrop_shader.bind();
        raindrop_shader.setUniformMat4f("projection", projection);
        raindrop_shader.setUniformMat4f("view", view);
        raindrop_texture.bind(0);
        for(Jokowi::Particle &raindrop: raindrops) {
            glm::mat4 raindrop_model = glm::mat4(1.0f);
            raindrop_model = glm::translate(raindrop_model, raindrop.GetPosition());
            raindrop_shader.setUniformMat4f("translate", raindrop_model);

            renderer.draw(raindrop_vao, 6, raindrop_shader);
            raindrop.Update(deltaTime);
        }

        // Smoke
        smoke_shader.bind();
        smoke_shader.setUniformMat4f("projection", projection);
        smoke_shader.setUniformMat4f("view", view);
        smoke_texture.bind(0);
        for(Jokowi::Particle &smoke: smokes) {
            glm::mat4 smoke_model = glm::mat4(1.0f);
            smoke_model = glm::translate(smoke_model, smoke.GetPosition());
            smoke_shader.setUniformMat4f("translate", smoke_model);

            renderer.draw(smoke_vao, 6, smoke_shader);
            smoke.Update(deltaTime);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) { 
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}