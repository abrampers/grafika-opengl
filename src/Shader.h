#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

struct ShaderProgramSource {
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader {
private:
    std::string m_filepath;
    unsigned int m_renderer_id;
    std::unordered_map<std::string, int> m_uniform_location_cache;

    int getUniformLocation(const std::string& name);

    // Caching uniforms

    ShaderProgramSource parseShader(const std::string& filepath);
    unsigned int compileShader(unsigned int type, const std::string& source);
    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
public:
    Shader(const std::string& filepath);
    ~Shader();

    void bind() const;
    void unbind() const;


    // set uniforms
    void setUniform1i(const std::string& name, int value);
    void setUniform1f(const std::string& name, float value);
    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
};
