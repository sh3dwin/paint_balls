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
	float _bounce;
	unsigned int number_of_bounces;

	bool _solid;

	Projectile(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float velocity) {
		_ball = new Sphere(position, 0.1f, GL_TRUE, glm::vec3(1.0));
		_position = position;
		_direction = direction;
		_color = glm::vec3(1.0);
		_velocity = velocity;
		_gravity = 0;
		_solid = true;
		_bounce = 0;
		number_of_bounces = 0;
	}

	~Projectile() {
		delete _ball;
	}

	void changeColor() {
		if (_color.x == 1.0f && _color.y == 0.0f) {
			_color = glm::vec3(GREEN);
		}
		else {
			if (_color.y == 1.0f && _color.x == 0.0f) {
				_color = glm::vec3(BLUE);
			}
			else {
				_color = glm::vec3(RED);
			}
		}
		number_of_bounces++;
		_ball->changeColor();
	}

	void Update(GLfloat dt) {
		this->_ball->direction = this->_direction;
		starting_y = _position.y;
		_position += _direction * _velocity * dt;
		_gravity += 10 * dt / 100;
		_velocity -= 0.01;
		_position.y -= _gravity;
		_position.y += _bounce;
		if(_bounce > 0)
			_bounce -= 15 * dt / 100;
		this->_ball->_position = _position;
		delta_y = starting_y - _position.y;
		if (_position.y <= -5.0f || _position.x > 500.0f || _position.z > 500.0f || _position.y >= 500.5f || _position.x < -500.0f || _position.z < -500.0f || number_of_bounces > 8) {
			_solid = false;
		}

	}

	void Bounce(){
		this->_bounce += abs(delta_y);
		this->_gravity -= _bounce;
	}

	void Draw(Camera* camera, std::vector<Light*> lights) {
		//std::cout << "PROJECTILE: DRAWING AT" << _position.x  << " " << _position.y  << " " << _position.z << "..." << std::endl;
		this->_ball->Draw(camera, lights);
	}
private:
	float starting_y;
	float delta_y;
};