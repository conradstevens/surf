#ifndef GLFW_ANCILLARY_H
#define GLFW_ANCILLARY_H
#include "GLFW/glfw3.h"


void glClearError();
void setCallBacks(GLFWwindow* window);
void glCheckError();
GLFWwindow* initWindow();

#endif //GLFW_ANCILLARY_H
