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

bool debug = false;


Game::Game(GLuint width, GLuint height, Camera camera)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height), _camera(camera)
{
    _camera.Position = glm::vec3(5.0f, 0.0f, 5.0f);
    _ammunition = 100;
    this->_level_renderer = new LevelRenderer();
    this->_overlay_renderer = new OverlayRenderer();
    this->skybox = new SkyBox();
}

Game::~Game()
{

}

void Game::Init()
{
    ResourceManager::LoadShader("resources/shaders/light_shader.vert", "resources/shaders/light_shader.frag", nullptr, "light");
    ResourceManager::LoadShader("resources/shaders/multiple_lights.vert", "resources/shaders/multiple_lights.frag", nullptr, "lightingShader");
    ResourceManager::LoadShader("resources/shaders/overlay.vert", "resources/shaders/overlay.frag", nullptr, "ammunitionShader");
    ResourceManager::LoadShader("resources/shaders/skybox.vert", "resources/shaders/skybox.frag", nullptr, "skybox");


    std::vector<std::string> faces
    {
        ("resources/textures/skybox/nightsky_east.bmp"),
        ("resources/textures/skybox/nightsky_west.bmp"),
        ("resources/textures/skybox/nightsky_up.bmp"),
        ("resources/textures/skybox/nightsky_down.bmp"),
        ("resources/textures/skybox/nightsky_north.bmp"),
        ("resources/textures/skybox/nightsky_south.bmp")
    };

    ResourceManager::loadCubemap(faces, GL_FALSE, "skybox");

    ResourceManager::LoadTexture("resources/textures/wooden_wall.jpg", GL_FALSE, "wooden_wall");
    ResourceManager::LoadTexture("resources/textures/blue_brick_wall.jpg", GL_FALSE, "blue_brick_wall");
    ResourceManager::LoadTexture("resources/textures/brick_wall.jpg", GL_FALSE, "brick_wall");
    ResourceManager::LoadTexture("resources/textures/container.png", GL_FALSE, "container");
    ResourceManager::LoadTexture("resources/textures/marble.PNG", GL_FALSE, "marble");
    ResourceManager::LoadTexture("resources/textures/black_marble.jpg", GL_FALSE, "black_marble");
    ResourceManager::LoadTexture("resources/textures/marble_specular.jpg", GL_FALSE, "marble_specular");
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
                _walls.push_back(new Wall(glm::vec3((i / _size) * 2.0f, 0.0f, (i % _size) * 2.0f)));
            }
        }
    }
    catch (std::exception e) {
        std::cout << "ERROR::LEVEL_RENDERER: Initializing\n";
    }


    addLight(glm::vec3(10.f, 2.f, 13.f), glm::vec3(1.f, 0.0f, 0.0f));
    addLight(glm::vec3(5.0f, 2.0f, 3.0f), glm::vec3(0.f, 0.0f, 1.0f));
    addLight(glm::vec3(2.f, 2.f, 12.f), glm::vec3(0.f, 1.0f, 0.0f));
    addLight(glm::vec3(4.0f, 2.0f, 8.0f), glm::vec3(0.f, 1.0f, 1.0f));
    addLight(glm::vec3(6.f, 2.f, 11.f), glm::vec3(1.f, 1.0f, 0.0f));
    addLight(glm::vec3(14.0f, 2.0f, 1.0f), glm::vec3(1.f, 0.0f, 1.0f));
    addColoredCube(glm::vec3(10.f, 1.f, 13.f), glm::vec3(1.f, 0.0f, 0.0f));
    addColoredCube(glm::vec3(5.0f, 1.0f, 3.0f), glm::vec3(0.f, 0.0f, 1.0f));
    addColoredCube(glm::vec3(2.f, 1.f, 12.f), glm::vec3(0.f, 1.0f, 0.0f));
    addColoredCube(glm::vec3(4.0f, 1.0f, 8.0f), glm::vec3(0.f, 1.0f, 1.0f));
    addColoredCube(glm::vec3(6.f, 1.f, 11.f), glm::vec3(1.f, 1.0f, 0.0f));
    addColoredCube(glm::vec3(14.0f, 1.0f, 1.0f), glm::vec3(1.f, 0.0f, 1.0f));
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
    this->_lights.push_back(new Light(position, color, true));
}

void Game::addPlayer() {
    _player = new Sphere(glm::vec3(4.0f, this->_floor->_position.y + 0.2f, 4.0f), 0.2f, GL_TRUE);
}

void Game::Update(GLfloat dt)
{
    doCollisions();
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
            if (debug)
                std::cout << "CAMERA: Moving FORWARD..." << std::endl;
            if(!CheckCollision(glm::vec3(_camera.Position.x + _camera.Front.x * _camera.MovementSpeed * dt, _camera.Position.y, _camera.Position.z + _camera.Front.z * _camera.MovementSpeed * dt)))
                
                _camera.ProcessKeyboard(FORWARD, dt);
            else {
                _camera.ProcessKeyboard(FORWARD, dt, xInside(_camera.Position.x + _camera.Front.x * _camera.MovementSpeed * dt), zInside(_camera.Position.z + _camera.Front.z * _camera.MovementSpeed * dt));
            }
        }
        if (this->Keys[GLFW_KEY_S]) {
            if (debug)
                std::cout << "CAMERA: Moving BACKWARD..." << std::endl;
            if (!CheckCollision(glm::vec3(_camera.Position.x + _camera.Front.x * _camera.MovementSpeed * dt, _camera.Position.y, _camera.Position.z + _camera.Front.z * _camera.MovementSpeed * dt)))
                _camera.ProcessKeyboard(BACKWARD, dt);
            else {
                _camera.ProcessKeyboard(BACKWARD, dt, xInside(_camera.Position.x + _camera.Front.x * _camera.MovementSpeed * dt), zInside(_camera.Position.z + _camera.Front.z * _camera.MovementSpeed * dt));
            }
        }
        if (this->Keys[GLFW_KEY_A]) {
            if (debug)
                std::cout << "CAMERA: Moving LEFT..." << std::endl;
            if (!CheckCollision(glm::vec3(_camera.Position.x + _camera.Front.x * _camera.MovementSpeed * dt, _camera.Position.y, _camera.Position.z + _camera.Front.z * _camera.MovementSpeed * dt)))
                _camera.ProcessKeyboard(LEFT, dt);
            else {
                _camera.ProcessKeyboard(LEFT, dt, xInside(_camera.Position.x + _camera.Front.x * _camera.MovementSpeed * dt), zInside(_camera.Position.z + _camera.Front.z * _camera.MovementSpeed * dt));
            }
        }
        if (this->Keys[GLFW_KEY_D]) {
            if (debug)
                std::cout << "CAMERA: Moving RIGHT..." << std::endl;
            if (!CheckCollision(glm::vec3(_camera.Position.x + _camera.Front.x * _camera.MovementSpeed * dt, _camera.Position.y, _camera.Position.z + _camera.Front.z * _camera.MovementSpeed * dt)))
                _camera.ProcessKeyboard(RIGHT, dt);
            else {
                _camera.ProcessKeyboard(RIGHT, dt, xInside(_camera.Position.x + _camera.Front.x * _camera.MovementSpeed * dt), zInside(_camera.Position.z + _camera.Front.z * _camera.MovementSpeed * dt));
            }
        }
        if (this->Keys[GLFW_MOUSE_BUTTON_LEFT]) {
            if (debug)
                std::cout << "PROJECTILE: CREATING..." << std::endl;
            float now = glfwGetTime();
            float dtt = now - _level_renderer->lastPressed;

            if (dtt > dt * 5) {
                _level_renderer->lastPressed = now;
                createProjectile();
            }
        }
        if (this->Keys[GLFW_KEY_F]) {
            if(debug)
                std::cout << "PROJECTILE: CREATING..." << std::endl;
            float now = glfwGetTime();
            float dtt = now - _level_renderer->lastPressed;

            if (dtt > dt * 5) {
                _level_renderer->lastPressed = now;
                Fire();
            }
        }
        if (this->Keys[GLFW_KEY_R]) {
            _camera.Position = glm::vec3(5.0f, 0.0f, 5.0f);
        }
        if (this->Keys[GLFW_KEY_H]) {
            float now = glfwGetTime();
            float dtt = now - _level_renderer->lastPressed;

            if (dtt > dt * 5){
                _level_renderer->lastPressed = now;
                _level_renderer->_draw = !_level_renderer->_draw;
            }
        }
        if (this->Keys[GLFW_KEY_V]) {
                debug = !debug;
        }

    }

}

void Game::Render(GLfloat dt)
{
    _level_renderer->draw(&_camera, _walls, _lights, _projectiles, _player, _floor, _colored_cubes, skybox);
    _overlay_renderer->draw(_ammunition);
}

void Game::doCollisions() {
    for (Projectile* projectile : _projectiles) {
        for (Wall* wall : _walls) {
            if (CheckCollision(projectile, wall)) {
                std::cout << "COLLISION: Detected!\n";
            }
        }
        for (Light* cube : _colored_cubes) {
            if (!cube->_destroyed && CheckCollision(projectile, cube)) {
                std::cout << "COLLISION: Detected!\n";
            }
        }
        if (projectile->_position.y < -0.4) {
            projectile->Bounce();
            projectile->changeColor();
        }
    }
}

GLboolean Game::CheckCollision(Projectile* projectile, Wall* wall) {

    float sphereXDistance = abs(projectile->_position.x - wall->_position.x);
    float sphereYDistance = abs(projectile->_position.y - wall->_position.y);
    float sphereZDistance = abs(projectile->_position.z - wall->_position.z);

    if (sphereXDistance >= (1 + projectile->_ball->radius)) { return false; }
    if (sphereYDistance >= (1 + projectile->_ball->radius)) { return false; }
    if (sphereZDistance >= (1 + projectile->_ball->radius)) { return false; }

    

    float cornerDistance_sq = ((sphereXDistance - 1) * (sphereXDistance - 1)) +
        ((sphereZDistance - 1) * (sphereZDistance - 1));

    if (cornerDistance_sq < (projectile->_ball->radius * projectile->_ball->radius)) {
        projectile->_direction.x = -projectile->_direction.x;
        projectile->_direction.z = -projectile->_direction.z;

        projectile->changeColor();
        return true;
    }

    if (sphereXDistance > sphereZDistance) {
        projectile->_direction.x = -projectile->_direction.x;
        projectile->changeColor();
        return true;
    }
    else {
        projectile->_direction.z = -projectile->_direction.z;
        projectile->changeColor();
        return true;
    }
    return false;
}

GLboolean Game::CheckCollision(Projectile* projectile, Light* cube) {
    float sphereXDistance = abs(projectile->_position.x - cube->_position.x);
    float sphereYDistance = abs(projectile->_position.y - cube->_position.y);
    float sphereZDistance = abs(projectile->_position.z - cube->_position.z);

    if (sphereXDistance >= (0.5 + projectile->_ball->radius)) { return false; }
    if (sphereYDistance >= (0.5 + projectile->_ball->radius)) { return false; }
    if (sphereZDistance >= (0.5 + projectile->_ball->radius)) { return false; }



    float cornerDistance_sq = ((sphereXDistance - 0.5) * (sphereXDistance - 0.5)) +
        ((sphereZDistance - 0.5) * (sphereZDistance - 0.5));

    if (cornerDistance_sq < (projectile->_ball->radius * projectile->_ball->radius)) {  
        cube->Hit(projectile->_color);
        projectile->_solid = false;
        return true;
    }

    if (sphereXDistance > sphereZDistance) {
        cube->Hit(projectile->_color);
        projectile->_solid = false;
        return true;
    }
    else {
        cube->Hit(projectile->_color);
        projectile->_solid = false;
        return true;
    }
    return false;
}

GLboolean Game::CheckCollision(glm::vec3 _position, float radius, Wall& wall) {
    bool checkX = (_position.x + radius) >= wall._position.x && (wall._position.x + 1.0f) >= _position.x + radius;
    bool checkY = (_position.y + radius) >= wall._position.y && (wall._position.y + 1.0f) >= _position.y + radius;
    bool checkZ = (_position.z + radius) >= wall._position.z && (wall._position.z + 1.0f) >= _position.z + radius;

    return checkX && checkY && checkZ;
}

GLboolean Game::CheckCollision(glm::vec3 playerPosition) {
    for (Wall* wall : _walls) {
        if (playerPosition.x <= wall->_position.x + 1.1 &&
            playerPosition.x >= wall->_position.x - 1.1 &&
            playerPosition.z <= wall->_position.z + 1.1 &&
            playerPosition.z >= wall->_position.z - 1.1) {
            std::cout << "Player position is (" << playerPosition.x << ", " << playerPosition.y << ", " << playerPosition.z << ") and the wall position is ("
                << wall->_position.x << "-" << wall->_position.x + 2.0 << ", " << wall->_position.y << "-" << wall->_position.y + 2.0 << ", " << wall->_position.z << "-" << wall->_position.z + 2.0 << ")\n";
            return true;
        }
    }
    return false;
}

GLboolean Game::xInside(float x) {
    for (Wall* wall : _walls) {
        if (x <= wall->_position.x + 1 &&
            x >= wall->_position.x - 1) {
            return true;
        }
    }
    return false;
}

GLboolean Game::zInside(float z) {
    for (Wall* wall : _walls) {
        if (z <= wall->_position.z + 1 &&
            z >= wall->_position.z - 1) {
            return true;
        }
    }
    return false;
}

void Game::createProjectile() {
    glm::vec3 color;
    float x = abs(rand() % 200) / 100.0;
    float y = abs(rand() % 200) / 100.0;
    float z = abs(rand() % 200) / 100.0;
    std::cout << x << " " << y << " " << z << "  ==================== COLOR\n";
    color = glm::vec3(x, y, z);
    this->_projectiles.push_back(new Projectile(_camera.Position + _camera.Front * glm::vec3(1.1), _camera.Front, color, 20));
}

void Game::addColoredCube(glm::vec3 position, glm::vec3 color) {
    this->_colored_cubes.push_back(new Light(position, color, false));
}

void Game::Fire() {
    if (_ammunition == 0)
        return;
    _ammunition -= 1;
    this->_overlay_renderer->PaintBallFired();
    createProjectile();
}
