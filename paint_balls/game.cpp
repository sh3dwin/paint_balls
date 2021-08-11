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
    this->_level_renderer = new LevelRenderer();
}

Game::~Game()
{

}

void Game::Init()
{
    ResourceManager::LoadShader("resources/shaders/light_shader.vert", "resources/shaders/light_shader.frag", nullptr, "light");
    ResourceManager::LoadShader("resources/shaders/multiple_lights.vert", "resources/shaders/multiple_lights.frag", nullptr, "lightingShader");
    ResourceManager::LoadTexture("resources/textures/wooden_wall.jpg", GL_FALSE, "wooden_wall");
    ResourceManager::LoadTexture("resources/textures/container.png", GL_FALSE, "container");
    ResourceManager::LoadTexture("resources/textures/container_specular.png", GL_FALSE, "container_specular");
    ResourceManager::LoadTexture("resources/textures/tile_diffuse.jpg", GL_FALSE, "tile_diffuse");
    ResourceManager::LoadTexture("resources/textures/tile_specular.jpg", GL_FALSE, "tile_specular");

    _size = 10;

    unsigned int layout[100] = 
    {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 1, 0, 0, 1,
        1, 1, 1, 0, 0, 0, 1, 0, 0, 1,
        1, 0, 1, 0, 1, 0, 1, 0, 0, 1,
        1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 1, 1, 1, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 1, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };
    _layout = new unsigned int[100];
    _layout = layout;

    _floor = new Floor(glm::vec3(0.f, -0.5f, 0.f));
    try {
        std::cout << "LEVEL_RENDERER: Initializing...\n";
        for (unsigned int i = 0; i < _size * _size; i++) {
            if (_layout[i] == 1) {
                std::cout << "LEVEL_RENDERER: PSUHGING...\n";
                _walls.push_back(new Wall(glm::vec3((i / _size) * 1.0f, 0.0f, (i % _size) * 1.0f)));
            }
        }
    }
    catch (std::exception e) {
        std::cout << "ERROR::LEVEL_RENDERER: Initializing\n";
    }


    addLight(glm::vec3(2.f, 1.f, 2.f), glm::vec3(1.f, 0.0f, 0.0f));
    addLight(glm::vec3(4.0f, 1.0f, 3.0f), glm::vec3(0.f, 0.0f, 1.0f));
    addPlayer();
}

void Game::generateLayout(unsigned int layout[], unsigned int size){
    std::cout << "LEVEL_RENDERER: Creating..." << std::endl;
    try {
        _size = size;
        std::cout << "LEVEL_RENDERER: Generating layout..." << std::endl;
        for (unsigned int i = 0; i < size * size; i++) {
            _layout[i] = layout[i];
            std::cout << _layout[i] << "\n";
        }
    }
    catch (std::exception e) {
        std::cout << "ERROR::LEVEL_RENDERER: Failed to create a Level Renderer" << std::endl;
    }
    std::cout << "Created a renderer successfully" << std::endl;
}

void Game::Load(const GLchar* file, unsigned int size) {
    try {
        if (size <= 0) {
            std::cout << "Layout size is smaller or equal to 0!\n";
            return;
        }
        char destination[] = "../resources/levels/";
        std::ifstream f(strcat(destination, file));
        std::string line;
        if (f) {
            for (unsigned int i = 0; i < size; i++) {
                std::getline(f, line);
                for (unsigned int j = 0; j < size; j++) {
                    _layout[i * size + j] = (unsigned int)line[j] - '0';
                }
            }
        }
    }
    catch (std::exception e) {
        std::cout << "ERROR::LEVEL_RENDERER: Failed to LOAD a Level Layout" << std::endl;
    }
}

void Game::addLight(glm::vec3 position, glm::vec3 color) {
    this->_lights.push_back(new Light(position, color));
}

void Game::addPlayer() {
    _player = new Sphere(glm::vec3(4.0f, this->_floor->_position.y + 0.2f, 4.0f), 0.2f, GL_TRUE);
}

void Game::Update(GLfloat dt)
{
    for (int i = 0; i < _projectiles.size(); i++) {
        _projectiles[i]->Update(dt);
        if (!_projectiles[i]->_solid) {
            _projectiles.erase(_projectiles.begin() + i);
        }
    }
    for (Light* light : _lights) {
        light->Update(dt);
    }
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
        if (this->Keys[GLFW_MOUSE_BUTTON_LEFT]) {
            std::cout << "PROJECTILE: CREATING..." << std::endl;
            _projectiles.push_back(new Projectile(_camera.Position, _camera.Front, glm::vec3(1.0f, 1.0f, 1.0f), 50));
        }
        if (this->Keys[GLFW_KEY_F]) {
            
            std::cout << "PROJECTILE: CREATING..." << std::endl;
            float now = glfwGetTime();
            float dtt = now - _level_renderer->lastPressed;

            if (dtt > dt * 5 || true) {
                _level_renderer->lastPressed = now;
                createProjectile();
            }
        }
        if (this->Keys[GLFW_KEY_H]) {
            float now = glfwGetTime();
            float dtt = now - _level_renderer->lastPressed;

            if (dtt > dt * 5){
                _level_renderer->lastPressed = now;
                _level_renderer->_draw = !_level_renderer->_draw;
            }
        }

    }

}

void Game::Render(GLfloat dt)
{
    _level_renderer->draw(&_camera, _walls, _lights, _projectiles, _player, _floor);
}

void Game::doCollisions() {

}

GLboolean Game::CheckCollision(glm::vec3 position, Wall& wall) {

}

GLboolean Game::CheckCollision(glm::vec3 _position, float radius, Wall& wall) {
    bool checkX = (_position.x + radius) >= wall._position.x && (wall._position.x + 1.0f) >= _position.x - radius;
    bool checkY = (_position.y + radius) >= wall._position.y && (wall._position.y + 1.0f) >= _position.y - radius;
    bool checkZ = (_position.z + radius) >= wall._position.z && (wall._position.z + 1.0f) >= _position.z - radius;

    return checkX && checkY && checkZ;
}

GLboolean Game::CheckCollision(Sphere& projectile, Sphere& ball) {

}

void Game::createProjectile() {
    glm::vec3 color;
    float x = abs(rand() % 200) / 100.0;
    float y = abs(rand() % 200) / 100.0;
    float z = abs(rand() % 200) / 100.0;
    std::cout << x << " " << y << " " << z << "  ==================== COLOR\n";
    color = glm::vec3(x, y, z);
    this->_projectiles.push_back(new Projectile(_camera.Position, _camera.Front, color, 10));
}

