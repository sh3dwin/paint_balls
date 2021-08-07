#pragma once

#include <Gl/glew.h>
#include <glm/glm.hpp>
#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <vector>

class Sphere {
public:



	bool textured;

	unsigned int VAO;
	unsigned int lineVAO;
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 Angle = glm::vec3(-90.0f, 0.0f, 0.0f);
	glm::mat4 model = glm::mat4(1.0f);
	unsigned int numVertices = 0;
	unsigned int numIndices = 0;
	unsigned int numLineIndices = 0;
	float radius;
	Shader shader;
	std::vector<float> vertices;
	int hLines;
	int vLines;
	std::vector<unsigned int> indices;
	std::vector<unsigned int> lineIndices;

	/**
	 * Creates a Sphere at global position (x, y, z) with radius r
	 *
	 * @param horizontal_smoothness - integer number ( > 2) that defines the number of vertical lines (longitude)
	 * @param vertical_smoothness -  integer number ( > 2) that defines the number of horizontal lines (latitude)
	 * @param shader - The shader which the sphere will be drawn with
	*/
	Sphere(float x, float y, float z, float r, int horizontal_smoothness, int vertical_smoothness, Shader shader, bool Textured) {
		this->textured = Textured;
		this->model = glm::rotate(model, glm::radians(this->Angle.x), glm::vec3(0.0f, 1.0f, .0f));
		this->hLines = horizontal_smoothness;
		this->vLines = vertical_smoothness;
		this->shader = shader;
		this->Position = glm::vec3(x, y, z);
		this->radius = r;
		this->numVertices = 0;
		this->numIndices = 0;
		this->VAO = 0;
		this->lineVAO = 0;
		if (r == 0.0f)
			return;
		getVertices(); // get the array of vertices that define the sphere at Position
		getIndicies(); // get the indices
		setVAO();
		setLineVao();

	}

	void setVAO() {
		float* v = new float[numVertices];
		for (int i = 0; i < numVertices; i++) {
			v[i] = vertices[i];
		}
		unsigned int* o = new unsigned int[numIndices];
		for (int i = 0; i < numIndices; i++) {
			o[i] = indices[i];
		}

		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices, v, GL_STATIC_DRAW);

		unsigned int EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, o, GL_STATIC_DRAW);

		if (this->textured) {
			glBindVertexArray(VAO);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));
			glEnableVertexAttribArray(1);
		}
		else {
			glBindVertexArray(VAO);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
		}

		delete[] v;
		delete[] o;
		//this->vertices.clear();
		this->indices.clear();

		this->VAO = VAO;
	}

	void setLineVao() {
		float* v = new float[numVertices];
		for (int i = 0; i < numVertices; i++) {
			v[i] = vertices[i] * 1.0001f;

		}
		unsigned int* o = new unsigned int[numLineIndices];
		for (int i = 0; i < numLineIndices; i++) {
			o[i] = lineIndices[i];
		}
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		this->lineVAO = VAO;
		glBindVertexArray(VAO);

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices, v, GL_STATIC_DRAW);

		unsigned int EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numLineIndices, o, GL_STATIC_DRAW);

		if (this->textured) {
			glBindVertexArray(VAO);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));
			//glEnableVertexAttribArray(1);
		}
		else {
			glBindVertexArray(VAO);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
		}


	}

	/**
	 * Returns the vertices of a sphere with class param radius, hLines, vLines
	 * @returns Float array containing said vertices
	*/
	void getVertices() {
		std::vector<float> verticesV;
		std::vector<float> lineVerticesV;
		const float pi = 3.141592f;

		float x_pos, y_pos, z_pos, xy;

		float verticalStep = pi / this->vLines;
		float horizontalStep = 2 * pi / this->hLines;
		float vertAngle = 0, horzAngle = 0;
		float s = 0;
		float t = 0;

		for (float i = 0; i <= this->vLines; i++) {
			vertAngle = pi / 2 - (i * verticalStep);
			xy = this->radius * cos(vertAngle);
			z_pos = this->radius * sin(vertAngle);

			for (int j = 0; j <= this->hLines; j++) {
				horzAngle = j * horizontalStep;

				x_pos = xy * cos(horzAngle);
				y_pos = xy * sin(horzAngle);


				verticesV.push_back(x_pos);
				verticesV.push_back(y_pos);
				verticesV.push_back(z_pos);


				this->numVertices += 3;

				if (this->textured) {
					s = (float)j / hLines;
					t = (float)i / vLines;
					verticesV.push_back(s);
					verticesV.push_back(t);

					this->numVertices += 2;
				}

			}
		}
		this->vertices = verticesV;
	}

	/**
	 * Returns the indecies of the vertices of the sphere
	 * @returns Float array containing said vertices
	*/
	void getIndicies() {
		std::vector<unsigned int> indicesV;
		std::vector<unsigned int> lineIndicesV;

		unsigned int p1 = 0, p2 = 0;

		for (int i = 0; i < this->vLines; ++i) {
			p1 = i * (this->hLines + 1);
			p2 = p1 + this->hLines + 1;

			for (int j = 0; j < this->hLines; ++j, ++p1, p2++) {
				if (i != 0) {
					indicesV.push_back(p1);
					indicesV.push_back(p2);
					indicesV.push_back(p1 + 1);
					//printf("(%d, %d, %d)\n", p1, p2, p1 + 1);
					this->numIndices += 3;
				}

				if (i != vLines - 1) {
					indicesV.push_back(p1 + 1);
					indicesV.push_back(p2);
					indicesV.push_back(p2 + 1);
					this->numIndices += 3;
					//printf("(%d, %d, %d)\n", p1 + 1, p2, p2 + 1);
				}

				lineIndicesV.push_back(p1);
				lineIndicesV.push_back(p2);
				this->numLineIndices += 2;
				if (i != 0)
				{
					lineIndicesV.push_back(p1);
					lineIndicesV.push_back(p1 + 1);
					this->numLineIndices += 2;
				}

			}
		}
		this->indices = indicesV;
		this->lineIndices = lineIndicesV;
	}




	void printArr() {
		for (int i = 0; i < this->numVertices; i += 5) {
			std::cout << this->vertices[i] << " " << this->vertices[i + 1] << " " << this->vertices[i + 2] << "\n Texture: " << this->vertices[i + 3] << " " << this->vertices[i + 4] << "\n";
		}
		std::cout << std::endl;
		for (int i = 0; i < this->numIndices; i++) {
			std::cout << this->indices[i] << " ";
		}
		std::cout << std::endl;
	}
	/*
	void setVertices(std::vector<float> vector) {
		this->vertices = new float[vector.size()];
		std::cout << "Size: " << vector.size() << std::endl;
		for (int i = 0; i < vector.size(); i++) {
			this->vertices[i] = vector[i];
		}
	}

	void setIndices(std::vector<unsigned int> vector) {
		this->indices = new unsigned int[vector.size()];
		std::cout << "Size: " << vector.size() << std::endl;
		for (int i = 0; i < vector.size(); i++) {
			this->indices[i] = vector[i];
		}
	}*/

};