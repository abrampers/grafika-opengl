#include "VertexBuffer.h"
#include "Renderer.h"
#include <iostream>

Jokowi::VertexBuffer::VertexBuffer() {
    GLCall(glGenBuffers(1, &m_renderer_id));
}

Jokowi::VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
    GLCall(glGenBuffers(1, &m_renderer_id));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

Jokowi::VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &m_renderer_id));
}

void Jokowi::VertexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
}

void Jokowi::VertexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Jokowi::VertexBuffer::setData(const void *data, unsigned int size) const {
    std::cout << data << std::endl;
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}