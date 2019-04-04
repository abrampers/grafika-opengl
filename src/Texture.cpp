#include "Texture.h"
#include "stb_image/stb_image.h"

#include <iostream>

Texture::Texture(const std::string& filepath): m_renderer_id(0), m_filepath(filepath), m_local_buffer(nullptr), m_height(0), m_width(0), m_bpp(0) {
    stbi_set_flip_vertically_on_load(1);
    m_local_buffer = stbi_load(m_filepath.c_str(), &m_width, &m_height, &m_bpp, 4);

    GLCall(glGenTextures(1, &m_renderer_id));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_renderer_id));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer));
    GLCall(glGenerateMipmap(m_renderer_id));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (m_local_buffer)
        stbi_image_free(m_local_buffer);
    else 
        std::cout << "Failed to load texture" << std::endl;
}

Texture::~Texture() {
    GLCall(glDeleteTextures(1, &m_renderer_id));
}

void Texture::bind(unsigned int slot) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_renderer_id));
}

void Texture::unbind() const {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}