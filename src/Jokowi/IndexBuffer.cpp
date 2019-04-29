#include "IndexBuffer.h"
#include "Renderer.h"

Jokowi::IndexBuffer::IndexBuffer() : m_count(0) {
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_renderer_id));
}

Jokowi::IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : m_count(count) {
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_renderer_id));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

Jokowi::IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &m_renderer_id));
}

void Jokowi::IndexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
}

void Jokowi::IndexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Jokowi::IndexBuffer::setData(const unsigned int *data, unsigned int count) {
    m_count = count;
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}