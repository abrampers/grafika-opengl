#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <stb_image/stb_image.h>

// Instantiate static variables
std::map<std::string, Breakout::Texture2D*>    Breakout::ResourceManager::Textures;
std::map<std::string, Breakout::Shader*>       Breakout::ResourceManager::Shaders;


Breakout::Shader * Breakout::ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, const std::string & name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Breakout::Shader * Breakout::ResourceManager::GetShader(const std::string & name)
{
    return Shaders[name];
}

Breakout::Texture2D * Breakout::ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, const std::string & name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Breakout::Texture2D * Breakout::ResourceManager::GetTexture(const std::string & name)
{
    return Textures[name];
}

void Breakout::ResourceManager::Clear()
{
    // (Properly) delete all shaders
    for (auto iter : Shaders)
    {
        glDeleteProgram(iter.second->ID);
        delete iter.second;
    }

    // (Properly) delete all textures
    for (auto iter : Textures)
    {
        glDeleteTextures(1, &iter.second->ID);
        delete iter.second;
    }
}

Breakout::Shader * Breakout::ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // If geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    const GLchar *gShaderCode = geometryCode.c_str();
    // 2. Now create shader object from source code
    Breakout::Shader * shader = new Shader();
    shader->Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Breakout::Texture2D * Breakout::ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
{
    // Create Texture object
    Breakout::Texture2D * texture = new Texture2D();
    if (alpha)
    {
        texture->Internal_Format = GL_RGBA;
        texture->Image_Format    = GL_RGBA;
    }
    // Load image
    int width, height;
    unsigned char* image = stbi_load(file, &width, &height, nullptr, texture->Image_Format == GL_RGBA ? 4 : 3);
    // Now generate texture
    texture->Generate(width, height, image);
    // And finally free image data
    stbi_image_free(image);
    return texture;
}