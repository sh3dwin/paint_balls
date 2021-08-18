#pragma once

/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#define GLEW_STATIC
#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "game.h"
#include "resource_manager.h"


// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// The Width of the screen
const GLuint SCREEN_WIDTH = 1920;
// The height of the screen
const GLuint SCREEN_HEIGHT = 1080;

float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame


// The Camera Object


// Game Object
Game PaintBalls(SCREEN_WIDTH, SCREEN_HEIGHT, Camera(glm::vec3(0.0f, 0.0f, 3.0f)));

int main(int argc, char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PaintBalls", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewInit();
    glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);



    // OpenGL configuration
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialize game
    PaintBalls.Init();

    // DeltaTime variables
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    // Start Game within Menu State
    PaintBalls.State = GAME_ACTIVE;

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        // Manage user input
        PaintBalls.ProcessInput(deltaTime);
        //std::cout << "CAMERA POSITION: " << PaintBalls._camera.Position.x << " " << PaintBalls._camera.Position.y << " " << PaintBalls._camera.Position.z << "\n";

        // Update Game state
        PaintBalls.Update(deltaTime);

        // Render
        PaintBalls.Render(deltaTime);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Delete all resources as loaded using the resource manager
    ResourceManager::Clear();

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            PaintBalls.Keys[key] = GL_TRUE;
        else if (action == GLFW_RELEASE)
            PaintBalls.Keys[key] = GL_FALSE;
    }
    
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (PaintBalls.firstMouse)
    {
        PaintBalls.lastX = xpos;
        PaintBalls.lastY = ypos;
        PaintBalls.firstMouse = false;
    }

    float xoffset = xpos - PaintBalls.lastX;
    float yoffset = PaintBalls.lastY - ypos; // reversed since y-coordinates go from bottom to top

    PaintBalls.lastX = xpos;
    PaintBalls.lastY = ypos;

    PaintBalls._camera.ProcessMouseMovement(xoffset, yoffset);

    std::cout << "CAMERA: Pitch " << PaintBalls._camera.Pitch << std::endl;
    std::cout << "CAMERA: Yaw " << PaintBalls._camera.Yaw << std::endl;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    
}