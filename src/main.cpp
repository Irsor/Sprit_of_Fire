#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_program.hpp"

void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

int main() {

    if (!glfwInit()) {
        std::cerr << "GLFW init error" << std::endl;
        return -1;
    }

    atexit(glfwTerminate);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Spirit of Fire", nullptr, nullptr);
    if (!window) {
        std::cerr << "GLFW window creation error" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "GLAD initialization error" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    auto vertexShaderPath = "../shaders/vertex_shader.glsl";
    auto fragmentShaderPath = "../shaders/fragment_shader.glsl";

    ShaderProgram program(vertexShaderPath, fragmentShaderPath);

    std::vector<glm::vec3> vertices = {
            { -0.5f, -0.5f, 0.0f },
            { 1.0f, 0.0f, 0.0f },
            { 0.5f, -0.5f, 0.0f },
            { 0.0f, 1.0f, 0.0f },
            { 0.5f, 0.5f, 0.0f },
            { 0.0f, 0.0f, 1.0f },
            { -0.5f, 0.5f, 0.0f },
            { 1.0f, 1.0f, 0.0f }
    };

    std::vector<GLuint> indices = { 0, 1, 3, 2, 3, 1 };

    GLuint VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * vertices.size() * 3, vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Shaders
        program.use();

        GLfloat timeValue = glfwGetTime();
        GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
        GLint vertexColorLocation = glGetUniformLocation(program.getProgram(), "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // Draw triangle
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();

    return 0;
}