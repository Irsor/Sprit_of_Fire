#pragma once

#include <string>
#include <glad/glad.h>
#include "utils/file_utils.hpp"

class ShaderProgram {
public:
    ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    GLuint getProgram() const;
    void use() const;

private:
    GLuint createShader(const std::string& shaderSource, GLenum shaderType);

    GLuint program;
};