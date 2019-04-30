#include "Renderer.h"
#include <iostream>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

Jokowi::Renderer::Renderer(/* args */) {

}

Jokowi::Renderer::~Renderer() {

}

void Jokowi::Renderer::clear(bool withColor) const {
    if (withColor)
        glClearColor(150.0f/255.0f, 180.0f/255.0f, 241.0f/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Jokowi::Renderer::draw(const VertexArray& va, unsigned int no_vertex, const Shader& shader) const {
    shader.bind();
    va.bind();
    glDrawArrays(GL_TRIANGLES, 0, no_vertex);
}

void Jokowi::Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    shader.bind();
    va.bind();
    ib.bind();

    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}