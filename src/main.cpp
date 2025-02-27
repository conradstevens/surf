#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE  //  Ensures gl3.h is included rather than gl.h
#include <iostream>
#include <GLFW/glfw3.h>  // OpenGL includes after include glfw3
#include <OpenGL/gl3.h>
#include "rendering/glfw_ancillary.h"
#include "scenes/scene.h"

using namespace glfw_rendering;


int main()
{
    GLFWwindow* window = initWindow();
    Scene scene{};

    scene.start();
    while (!glfwWindowShouldClose(window))
    {
        // OpenGL Rendering related code
        glClear(GL_COLOR_BUFFER_BIT);
        glClearError();

        scene.render();

        glCheckError();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
