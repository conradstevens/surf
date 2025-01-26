#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE  //  Ensures gl3.h is included rather than gl.h
#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>  // OpenGL includes after include glfw3
#include <OpenGL/gl3.h>
#include "glfw_ancillary.h"
#include "ball.h"
#include "scene.h"
#include "snow_scene.h"


int main()
{
    GLFWwindow* window = initWindow();
    SnowScene snow_scene{};

    snow_scene.spawn_random_snow();

    snow_scene.startRender();
    while (!glfwWindowShouldClose(window))
    {
        // OpenGL Rendering related code
        glClear(GL_COLOR_BUFFER_BIT);
        glClearError();

        snow_scene.render();

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
