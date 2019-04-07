#pragma once

#include "glm/glm.hpp"

const unsigned int VERTEX_ = 1234;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec2 Tangent;
    glm::vec2 Bitangent;
};