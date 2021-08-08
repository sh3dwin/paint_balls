#pragma once

/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game.h"




Game::Game(GLuint width, GLuint height, Camera camera)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height), _camera(camera)
{
}

Game::~Game()
{

}

void Game::Init()
{
    ResourceManager::LoadShader("light_shader.vert", "light_shader.frag", nullptr, "light");
    ResourceManager::LoadShader("multiple_lights.vert", "multiple_lights.frag", nullptr, "wooden_wall");
    ResourceManager::LoadTexture("../resources/textures/wooden_wall.jpg", GL_FALSE, "wooden_wall");
    ResourceManager::LoadTexture("../resources/textures/container.png", GL_FALSE, "container");
    ResourceManager::LoadTexture("../resources/textures/container_specular.png", GL_FALSE, "container_specular");


    _level_renderer = new LevelRenderer(new unsigned int[9]{1, 1, 0, 0, 0, 0, 1, 0, 0}, 3);
    _level_renderer->addLight(glm::vec3(2.f, 2.f, 2.f), glm::vec3(1.f, 0.0f, 0.0f));
    _level_renderer->addLight(glm::vec3(1.0f, -2.0f, 3.0f), glm::vec3(0.f, 0.0f, 1.0f));
}

void Game::Update(GLfloat dt)
{

}


void Game::ProcessInput(GLfloat dt)
{
    if (this->State == GAME_ACTIVE) {
        if (this->Keys[GLFW_KEY_W]) {
            std::cout << "CAMERA: Moving FORWARD..." << std::endl;
            _camera.ProcessKeyboard(FORWARD, dt);
        }
        if (this->Keys[GLFW_KEY_S]) {
            std::cout << "CAMERA: Moving BACKWARD..." << std::endl;
            _camera.ProcessKeyboard(BACKWARD, dt);
        }
        if (this->Keys[GLFW_KEY_A]) {
            std::cout << "CAMERA: Moving LEFT..." << std::endl;
            _camera.ProcessKeyboard(LEFT, dt);
        }
        if (this->Keys[GLFW_KEY_D]) {
            std::cout << "CAMERA: Moving RIGHT..." << std::endl;
            _camera.ProcessKeyboard(RIGHT, dt);
        }

    }

}

void Game::Render(GLfloat dt)
{
    _level_renderer->draw(&_camera);
}

