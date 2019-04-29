#include "Shader.h"
#include "Renderer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "glm/gtc/type_ptr.hpp"

Jokowi::Shader::Shader(const std::string& filepath): m_filepath(filepath), m_renderer_id(0) {
    ShaderProgramSource source = parseShader(filepath);
    m_renderer_id = createShader(source.vertexSource, source.fragmentSource);
}

Jokowi::Shader::~Shader() {
    GLCall(glDeleteProgram(m_renderer_id));
}   


void Jokowi::Shader::bind() const {
    GLCall(glUseProgram(m_renderer_id));
}

void Jokowi::Shader::unbind() const {
    GLCall(glUseProgram(0));
}

int Jokowi::Shader::getUniformLocation(const std::string& name) {
    if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end()) {
        return m_uniform_location_cache[name];
    }

    GLCall(int location = glGetUniformLocation(m_renderer_id, name.c_str()));
    if (location == -1) {
        std::cout << "Warning: Uniform '" << name << "' doesn't exist!" << std::endl;
    }
    
    m_uniform_location_cache[name] = location;
    return location;
}

void Jokowi::Shader::setUniform1i(const std::string& name, int value) {
    GLCall(glUniform1i(getUniformLocation(name), value));
}

void Jokowi::Shader::setUniform1f(const std::string& name, float value) {
    GLCall(glUniform1f(getUniformLocation(name), value));
}

void Jokowi::Shader::setUniform3f(const std::string& name, float v0, float v1, float v2) {
    GLCall(glUniform3f(getUniformLocation(name), v0, v1, v2));
}

void Jokowi::Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Jokowi::Shader::setUniformVec3f(const std::string& name, const glm::vec3& vec) {
    GLCall(glUniform3f(getUniformLocation(name), vec.x, vec.y, vec.z));
}

void Jokowi::Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix) {
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
}


Jokowi::ShaderProgramSource Jokowi::Shader::parseShader(const std::string& filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int) type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Jokowi::Shader::compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }


    return id;
}

unsigned int Jokowi::Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}