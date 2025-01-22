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
    Ball ball{};

    scene.addEntity(ball);
    scene.bindEntities();

    // ball.mesh->bindToGPU();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {

        // OpenGL Rendering related code
        glClear(GL_COLOR_BUFFER_BIT);
        glClearError();

        ball.move(0.1f, 0.3f);
        scene.reBindEntities();

        glDrawElements(GL_TRIANGLES, scene.index_count, GL_UNSIGNED_INT, nullptr);

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