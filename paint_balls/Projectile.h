#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>

#include "resource_manager.h"
#include "Light.h"
#include "Sphere.h"



class Projectile {
public:
	glm::vec3 RED = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 GREEN = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 BLUE = glm::vec3(0.0f, 0.0f, 1.0f);
	Sphere* _ball;
	glm::vec3 _color;

	glm::vec3 _position;
	glm::vec3 _direction;

	float _velocity;
	float _gravity;

	bool _solid;

	Projectile(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float velocity) {
		_ball = new Sphere(position, 0.2f, GL_TRUE, RED);
		_position = position;
		_direction = direction;
		_color = RED;
		_velocity = velocity;
		_gravity = 0;
		_solid = true;
	}

	~Projectile() {
		delete _ball;
	}

	void changeColor() {
		_ball->changeColor();
	}

	void Update(GLfloat dt) {
		_position += _direction * _velocity * dt;
		_gravity += 0.1 * dt / 100;
		_position.y -= _gravity;
		this->_ball->_position = _position;
		if (_position.y <= -5.0f || _position.x > 500.0f || _position.z > 500.0f || _position.y >= 500.5f || _position.x < -500.0f || _position.z < -500.0f) {
			_solid = false;
		}
	}

	void Draw(Camera* camera, std::vector<Light*> lights) {
		//std::cout << "PROJECTILE: DRAWING AT" << _position.x  << " " << _position.y  << " " << _position.z << "..." << std::endl;
		this->_ball->Draw(camera, lights);
	}
};