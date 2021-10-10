#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>

#include "shader.h"
#include <glfw/glfw3.h>
#include "resource_manager.h"

class Light {
public:
	unsigned int id = 0;
	bool debug = false;
	void Debug() {
		this->debug = !debug;
	}
	Light(glm::vec3 position, glm::vec3 color, bool isLight, unsigned int id) {
		this->_isLight = isLight;
		this->id = id;
		this->_destroyed = false;
		time_of_creation = glfwGetTime();
		random = rand();
		_position = position;
		_color = color;
		float data[] = {
			// positions       
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f
		};

		unsigned int VAO, VBO;
		glGenVertexArrays(1, &VAO);

		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

		glBindVertexArray(VAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);

		this->_VAO = VAO;
	}

	void Draw(Camera* camera) {
		if (_destroyed && !_isLight)
			return;
		Shader* shader = ResourceManager::GetShader("light");
		shader->Use();

		shader->SetMatrix4("view", camera->GetViewMatrix());
		shader->SetMatrix4("projection", glm::perspective(glm::radians(45.0f), (float)1920 / (float)1080, 0.1f, 1000.0f));
		glm::mat4 model = glm::mat4(1.0f);
		shader->SetMatrix4("model", model);

		model = glm::translate(model, _position);
		if(_isLight)
			model = glm::scale(model, glm::vec3(0.1f));
		shader->SetMatrix4("model", model);
		shader->SetVector3f("aColor", _color * ((_isLight) ? 1 : (0.3f + abs(sinf(glfwGetTime() * 0.5 - time_of_creation * random) * cosf(glfwGetTime() - time_of_creation * random)))));		


		

		glBindVertexArray(_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUseProgram(0);
	}

	void Update(GLfloat dt) {
		if(!_destroyed)
			_position.y = _position.y + (dt * 0.5 * sinf(glfwGetTime() - time_of_creation * random) * cosf(glfwGetTime() - time_of_creation * random));
	}

	void Hit(glm::vec3 color) {
		if(debug)
			std::cout << "THE COLOR OF THE PROJECTILE ISSSS!!!! :::::: " << color.x << " " << color.y << " " << color.z << std::endl;
		if (color.x > 0.0f && color.y > 0.0f && color.z > 0.0f)
			return;
		this->_color.x -= color.x;
		this->_color.y -= color.y;
		this->_color.z -= color.z;
		if (_color.x <= 0.0f && _color.y <= 0.0f && _color.z <= 0.0f)
			this->_destroyed = true;
	}

public:
	glm::vec3 _position;
	glm::vec3 _color;
	bool _isLight;
	bool _destroyed;
	unsigned int _VAO;
private:
	float time_of_creation;
	int random;
};