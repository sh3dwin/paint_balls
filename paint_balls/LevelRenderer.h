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
#include "GameObject.h"
#include "Wall.h"
#include "Light.h"
#include "Floor.h"
#include "Sphere.h"




class LevelRenderer {
public:

	~LevelRenderer() {
	}


	void draw(Camera* camera,
	std::vector<Wall*> _walls,
	std::vector<Light*> _lights,
	std::vector<Sphere*> _players,
	Floor* _floor) {
		std::cout << "LEVEL_RENDERER: Drawing " << _walls.size() << " walls...\n";
		_floor->Draw(camera, _lights);
		for (Wall* wall : _walls) {
			wall->Draw(camera, _lights);
		}
		for (Sphere* player : _players) {
			std::cout << "LLEVEL_RENDERER: Rendering players...\n";
			player->Draw(camera, _lights);
		}
		for (Light* light : _lights) {
			light->Draw(camera);
		}

		
	}

	void Update(GLfloat dt) {

	}

private:

};