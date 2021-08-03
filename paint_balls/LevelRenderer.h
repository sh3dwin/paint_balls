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


class Wall {
public:
	Wall(glm::vec3 position) {

		_position = position;

		float data[] = {
			// positions          // normals           // texture coords
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
		};

		unsigned int VAO, VBO, EBO;
		glGenVertexArrays(1, &VAO);

		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

		glBindVertexArray(VAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0)  ;
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) ( 3 ));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) ( 6 ));
		glEnableVertexAttribArray(2);

		_VAO = VAO;
	}
	void Draw(glm::mat4 view) {
		Shader shader = ResourceManager::GetShader("wooden_wall");

		shader.setMat4("projection", glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 1000.0f));
		shader.setMat4("view", view);
		
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, _position);
		shader.setMat4("model", model);

		Texture2D texture = ResourceManager::GetTexture("wooden_wall");

		glActiveTexture(GL_TEXTURE0);
		texture.Bind();

		glBindVertexArray(_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

	}
protected:
	unsigned int _VAO;
	glm::vec3 _position;
};

class LevelRenderer {
public:

	LevelRenderer(unsigned int* layout, unsigned int size, Camera camera){
		_camera = new Camera;
		_camera = &camera;
		_size = size;
		_layout = new unsigned int* [size];
		for (int i = 0; i < size; i++) {
			_layout[i] = new unsigned int[size];
			for (int j = 0; i < size; j++) {
				_layout[i][j] = layout[i * size + j];
			}
		}
	}

	~LevelRenderer() {
		delete[] _layout;
	}

	void Load(const GLchar* file, unsigned int size) {
		if (size <= 0){
			std::cout << "Layout size is smaller or equal to 0!\n";
			return;
		}
		char destination[] = "../resources/levels/";
		unsigned int **new_layout = new unsigned int* [size];
		std::ifstream f(strcat(destination, file));
		std::string line;
		if (f) {
			for (int i = 0; i < size; i++) {
				std::getline(f, line);
				new_layout[i] = new unsigned int[size];
				for (int j = 0; j < size; j++) {
					new_layout[i][j] = (unsigned int)line[j] - '0';
				}
			}
		}
		delete[] _layout;
		_layout = new_layout;
	}

	void Init() {
		for (int i = 0; i < _size; i++) {
			for (int j = 0; j < _size; j++) {
				if (_layout[i][j] == 1) {
					_walls.push_back(Wall(glm::vec3(i * 1.0f, 0.0f, j * 1.0f)));
				}
			}
		}
	}

	void draw() {
		Texture2D texture = ResourceManager::GetTexture("wooden_wall");
		for (Wall w : _walls) {
			w.Draw(_camera->GetViewMatrix());
		}
	}

private:
	unsigned int** _layout;
	unsigned int _size;
	Camera* _camera;
	std::vector<Wall> _walls;
};