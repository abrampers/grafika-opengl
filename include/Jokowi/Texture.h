#pragma once

#include "Renderer.h"

namespace Jokowi {
class Texture {
private:
    unsigned int m_renderer_id;
    unsigned char *m_local_buffer;
    int m_width, m_height, m_bpp;
public:
    std::string type;
    std::string m_filepath;

    Texture(const std::string& filepath);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    inline int getWidth() const { return m_width; }
    inline int getHeight() const { return m_height; }
};
}
