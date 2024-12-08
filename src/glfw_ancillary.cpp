#include <iostream>
#include "GLFW/glfw3.h"


// Callbacks
void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void resize_callback(GLFWwindow* window, int width, int height) {
    std::cout << "Resized: " << width << " x " << height << std::endl;
}

void pose_callback(GLFWwindow* window, int xpos, int ypos) {
    std::cout << "Posed: " << xpos << " x " << ypos << std::endl;
}

// Main helpers
void set_call_backs(GLFWwindow* window) {
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, resize_callback);
    glfwSetWindowPosCallback(window, pose_callback);
}

GLFWwindow* initWindow() {
    // Initialize the library
    if (!glfwInit()) throw std::runtime_error("GLFW init failed");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // Without these two hints, nothing above OpenGL version 2.1 is supported
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(640, 480, "Surf", NULL, NULL);
    if (!window) throw std::runtime_error("GLFW window creation failed");
    set_call_backs(window);

    glfwMakeContextCurrent(window);
    return window;
}