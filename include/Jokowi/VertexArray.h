#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Jokowi {
class VertexBufferLayout;

class VertexArray {
private:
    unsigned int m_renderer_id;
public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void bind() const;
    void unbind() const;
};
}