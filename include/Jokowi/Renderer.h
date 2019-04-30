#pragma once

#include <GL/glew.h>
#include <exception>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) throw std::exception();

#ifdef DEBUG
    #define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
    #define GLCall(x) x
#endif

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

namespace Jokowi {
class Renderer {
private:
    /* data */
public:
    Renderer(/* args */);
    ~Renderer();

    void draw(const VertexArray& va, unsigned int no_vertex, const Shader& shader) const;
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void clear(bool withColor) const;
};
}

