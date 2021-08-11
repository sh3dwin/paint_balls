#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>
#include <vector>

#include "resource_manager.h"
#include "camera.h"
#include "Wall.h"
#include "Light.h"
#include "Floor.h"
#include "Sphere.h"
#include "Projectile.h"





class LevelRenderer {
public:
	LevelRenderer() {
		_draw = true;
		lastPressed = glfwGetTime();
	}
	~LevelRenderer() {
	}


	void draw(Camera* camera,
	std::vector<Wall*> _walls,
	std::vector<Light*> _lights,
	std::vector<Projectile*> _projectiles,
	Sphere* _player,
	Floor* _floor) {
		std::cout << "LEVEL_RENDERER: Drawing " << _walls.size() << " walls...\n";
		if(_draw){
			_floor->Draw(camera, _lights);
			for (Wall* wall : _walls) {
				wall->Draw(camera, _lights);
			}
		}
		for (Projectile* projectile : _projectiles) {
			projectile->Draw(camera, _lights);
		}
		std::cout << "LLEVEL_RENDERER: Rendering players...\n";
		//player->_position = camera->Position + (camera->Front * 1.0f);
		_player->Draw(camera, _lights);
		for (Light* light : _lights) {
			light->Draw(camera);
		}

		
	}

	void Update(GLfloat dt) {

	}

	bool _draw;
	float lastPressed;
};