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
#include "resource_manager.h"


Game::Game(GLuint width, GLuint height, Camera camera)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height), _camera(camera)
{

}

Game::~Game()
{

}

void Game::Init()
{
    ResourceManager::LoadShader("multiple_lights.vert", "multiple_lights.frag", nullptr, "wooden_wall");
    ResourceManager::LoadTexture("wooden_wall.jpg", GL_FALSE, "wooden_wall");


    _level_renderer = new LevelRenderer(new unsigned int[9]{1, 1, 0, 0, 0, 0, 1, 0, 0}, 3, _camera);
}

void Game::Update(GLfloat dt)
{
    _level_renderer->draw();
}


void Game::ProcessInput(GLfloat dt)
{

}

void Game::Render()
{

}

