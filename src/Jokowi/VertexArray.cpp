#include "VertexArray.h"
#include "VertexBufferLayout.h"

Jokowi::VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &m_renderer_id));
}

Jokowi::VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &m_renderer_id));
}

void Jokowi::VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    bind();
    vb.bind();
    const auto& elements = layout.getElements();
    unsigned int offset = 0;

    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void *) offset);
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}

void Jokowi::VertexArray::bind() const {
    GLCall(glBindVertexArray(m_renderer_id));
}

void Jokowi::VertexArray::unbind() const {
    GLCall(glBindVertexArray(0));
}