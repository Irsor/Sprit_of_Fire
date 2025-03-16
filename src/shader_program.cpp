#include "shader_program.hpp"

GLuint ShaderProgram::getProgram() const {
    return program;
}

ShaderProgram::ShaderProgram(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
    std::string vertexShaderSource = utils::loadFile(vertexShaderPath);
    GLuint vertexShader = createShader(vertexShaderSource, GL_VERTEX_SHADER);

    std::string fragmentShaderSource = utils::loadFile(fragmentShaderPath);
    GLuint fragmentShader = createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success{};
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "Shader program link error" << std::endl << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint ShaderProgram::createShader(const std::string& shaderSource, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    const char* sourceData = shaderSource.c_str();
    glShaderSource(shader, 1, &sourceData, nullptr);
    glCompileShader(shader);

    GLint success{};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        auto shaderTypeStr = shaderType == 35633 ? "Vertex" : "Fragment";
        std::cerr << shaderTypeStr << " shader compilation error" << std::endl << infoLog << std::endl;
        return -1;
    }

    return shader;
}

void ShaderProgram::use() const {
    glUseProgram(program);
}
