#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "LevelRenderer.h"

class GameObject {
public:
	glm::vec3 _position;
	glm::vec3 _Color;
	GLboolean _isVisible;

	GameObject() {
		_position = glm::vec3(1.0f);
		_Color = glm::vec3(0.0f);
		_isVisible = GL_FALSE;
	}

	GameObject(glm::vec3 position, glm::vec3 color, GLboolean isVisible) {
		_position = position;
		_Color = color;
		_isVisible = isVisible;
	}
	void Draw(glm::mat4 view) {};
};


#endif