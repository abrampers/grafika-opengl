#pragma once

class VertexBuffer {
private:
    unsigned int m_renderer_id;

public:
    VertexBuffer();
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
    void setData(const void *data, unsigned int size) const;
};