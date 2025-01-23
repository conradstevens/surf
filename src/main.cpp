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



int main()
{
    GLFWwindow* window = initWindow();
    Scene scene{};

    Ball::load();
    auto* ball_1 = new Ball{};
    auto* ball_2 = new Ball{};

    scene.addEntity(ball_1, 0.5f, 0.5f);
    scene.addEntity(ball_2, 0.5f, -0.5f);

    scene.startRender();
    int i{};
    bool d = true;
    while (!glfwWindowShouldClose(window))
    {
        i ++;
        // OpenGL Rendering related code
        glClear(GL_COLOR_BUFFER_BIT);
        glClearError();

        scene.render();/**/

        glCheckError();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();

        if (d && i > 50) {
            scene.removeEntity(ball_1);
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}