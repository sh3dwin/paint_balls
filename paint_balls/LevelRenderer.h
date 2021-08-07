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




class LevelRenderer {
public:

	LevelRenderer(unsigned int layout[], unsigned int size){
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
		this->Init();
	}

	~LevelRenderer() {
	}

	void addLight(glm::vec3 position, glm::vec3 color) {
		this->_lights.push_back(Light(position, color));
	}

	void Load(const GLchar* file, unsigned int size) {
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

	void Init() {
		try {
			std::cout << "LEVEL_RENDERER: Initializing...\n";
			for (unsigned int i = 0; i < _size * _size; i++) {
				if (_layout[i] == 1) {
					_walls.push_back(Wall(glm::vec3((i + 1 / _size) * 1.0f, 0.0f, (i % _size) * 1.0f)));
				}
			}
		}
		catch (std::exception e) {
			std::cout << "ERROR::LEVEL_RENDERER: Initializing\n";
		}
	}

	void draw(Camera& camera) {
		std::cout << "LEVEL_RENDERER: Drawing " << _walls.size() << " walls...\n";
		for (Wall w : _walls) {
			w.Draw(&camera);
		}
		for (Light light : _lights) {
			light.Draw(&camera);
		}
	}

private:
	mutable unsigned int _layout[100];
	unsigned int _size;
	std::vector<Wall> _walls;
	std::vector<Light> _lights;
};