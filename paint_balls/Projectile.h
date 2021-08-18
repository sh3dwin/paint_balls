#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>

#include "resource_manager.h"
#include "Light.h"
#include "Sphere.h"

class Projectile {
public:
	Sphere* _ball;
	glm::vec3 _color;

	glm::vec3 _position;
	glm::vec3 _direction;

	float _velocity;
	float _gravity;

	bool _solid;

	Projectile(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float velocity) {
		_ball = new Sphere(position, 0.2f, GL_TRUE, color);
		_position = position;
		_direction = direction;
		_color = color;
		_velocity = velocity;
		_gravity = 0;
		_solid = true;
	}

	~Projectile() {
		delete _ball;
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