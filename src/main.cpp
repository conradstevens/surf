#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE  //  Ensures gl3.h is included rather than gl.h
#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>  // OpenGL includes after include glfw3
#include <OpenGL/gl3.h>
#include "glfw_ancillary.h"
#include "ball.h"



int main()
{
    GLFWwindow* window = initWindow();
    Ball ball{};
    ball.mesh.bindToGPU();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Resize the viewport
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        // OpenGL Rendering related code
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(ball.mesh.program);
        glBindVertexArray(ball.mesh.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}