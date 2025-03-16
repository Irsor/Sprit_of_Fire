#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

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
    glClearColor(0.0f, 1.0f, 0.0f, 0.0f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}