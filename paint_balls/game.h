#pragma once


/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <glfw/glfw3.h>


#include "LevelRenderer.h"
#include "OverlayRenderer.h" 
#include "resource_manager.h"


// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    std::vector<Wall*> _walls;
    std::vector<Light*> _lights;
    std::vector<Light*> _colored_cubes;
    std::vector<Projectile*> _projectiles;
    Floor* _floor;
    Sphere* _player;
    Camera _camera;
    bool firstMouse = true;
    float lastX = 640, lastY = 360;

    // Game state
    GameState              State;
    GLboolean              Keys[1024];
    GLuint                 Width, Height;
    // Constructor/Destructor
    Game(GLuint width, GLuint height, Camera camera);
    ~Game();
    // Initialize game state (load all shaders/textures/levels)
    void Init();
    // GameLoop
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render(GLfloat dt);
    void generateLayout(unsigned int layout[], unsigned int size);
    void addLight(glm::vec3 position, glm::vec3 color);
    void addPlayer();
    void addColoredCube(glm::vec3 position, glm::vec3 color);
    void Load(const GLchar* file, unsigned int size);
    void Fire();
private:
    void doCollisions();
    void createProjectile();
    GLboolean CheckCollision(Projectile* projectile, Wall* wall);
    GLboolean CheckCollision(glm::vec3 _position, float radius, Wall& wall);
    GLboolean CheckCollision(Projectile* projectile, Light* cube);
    GLboolean CheckCollision(glm::vec3 playerPosition);
    GLboolean xInside(float x);
    GLboolean zInside(float z);
    LevelRenderer* _level_renderer;
    OverlayRenderer* _overlay_renderer;
    unsigned int* _layout;
    unsigned int _size;
    unsigned int _ammunition;

};

#endif

