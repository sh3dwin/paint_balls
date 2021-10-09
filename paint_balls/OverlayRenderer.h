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


class OverlayRenderer {
public:
	OverlayRenderer() {
		this->_ammunitionChanged = true;
		this->_ammunitionVAO = 0;
	}

	void draw(int amountOfPaintBallsLeft) {
		this->drawAmmunition(amountOfPaintBallsLeft);
	}

	void drawAmmunition(int amountOfPaintBallsLeft) {
		//if (_ammunitionChanged) {
		getAmmunitionVAO(amountOfPaintBallsLeft);
		//}

		Shader* shader = ResourceManager::GetShader("ammunitionShader");
		shader->Use();

		glm::vec3 color = glm::vec3(abs(sinf(glfwGetTime())), abs(cosf(glfwGetTime())), 1 - abs(sinf(glfwGetTime())));
		shader->SetVector3f("aColor", color);

		glBindVertexArray(_ammunitionVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glUseProgram(0);
	}

	void getAmmunitionVAO(int amountOfPaintBallsLeft) {
		float positionLeft = -0.8f;
		float positionRight = positionLeft + (float)amountOfPaintBallsLeft * 0.016f;
		float positionBottom = -0.9f;

		float data[] = {
			positionLeft,  positionBottom, 0.0f,
			positionLeft,   positionBottom + 0.025, 0.0f,
			positionRight,  positionBottom + 0.025, 0.0f,

			positionRight, positionBottom + 0.025, 0.0f,
			positionRight, positionBottom, 0.0f,
			positionLeft,  positionBottom, 0.0f,
		};



		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);


		glBindVertexArray(VAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		this->_ammunitionVAO = VAO;
		this->_ammunitionChanged = false;
	}

	void PaintBallFired() {
		_ammunitionChanged = true;
	}

private:
	bool _ammunitionChanged;
	unsigned int _ammunitionVAO;
};