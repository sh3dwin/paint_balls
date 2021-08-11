#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>

#include "shader.h"
#include <glfw/glfw3.h>
#include "resource_manager.h"

class Light {
public:
	Light(glm::vec3 position, glm::vec3 color) {
		time_of_creation = glfwGetTime();
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
		Shader* shader = ResourceManager::GetShader("light");
		shader->Use();

		shader->SetMatrix4("view", camera->GetViewMatrix());
		shader->SetMatrix4("projection", glm::perspective(glm::radians(45.0f), (float)1920 / (float)1080, 0.1f, 1000.0f));
		glm::mat4 model = glm::mat4(1.0f);
		shader->SetMatrix4("model", model);

		model = glm::translate(model, _position);
		model = glm::scale(model, glm::vec3(0.1f));
		shader->SetMatrix4("model", model);
		shader->SetVector3f("aColor", _color);

		

		glBindVertexArray(_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUseProgram(0);
	}

	void Update(GLfloat dt) {
		_position.y = _position.y + (dt * 0.5 * sinf(glfwGetTime() - time_of_creation) * cosf(glfwGetTime() - time_of_creation));
	}
public:
	glm::vec3 _position;
	glm::vec3 _color;
	unsigned int _VAO;
private:
	double time_of_creation;
};