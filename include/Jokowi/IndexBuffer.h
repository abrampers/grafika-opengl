#pragma once

namespace Jokowi
{
class IndexBuffer {
private:
    unsigned int m_renderer_id;
    unsigned int m_count;

public:
    IndexBuffer();
    IndexBuffer(const unsigned int *data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    void setData(const unsigned int *data, unsigned int count);

    inline unsigned int getCount() const {
        return m_count;
    }
};
}