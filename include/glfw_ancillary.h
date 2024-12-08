#ifndef GLFW_ANCILLARY_H
#define GLFW_ANCILLARY_H
#include "GLFW/glfw3.h"


// GLFW Callbacks
void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void resize_callback(GLFWwindow* window, int width, int height);
void pose_callback(GLFWwindow* window, int xpos, int ypos);

// Main helpers
void set_call_backs(GLFWwindow* window);
GLFWwindow* initWindow();

#endif //GLFW_ANCILLARY_H
