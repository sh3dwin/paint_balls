#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>

#include "shader.h"
#include "resource_manager.h"
#include "Light.h"

class Sphere {
public:
	float last = 0;
	glm::vec3 direction;
	glm::vec3 RED = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 GREEN = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 BLUE = glm::vec3(0.0f, 0.0f, 1.0f);


	~Sphere() {

	}

	bool textured;

	unsigned int _VAO;
	unsigned int lineVAO;
	glm::vec3 _position;
	glm::vec3 _color;
	float radius;

	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> texCoords;

	int hLines;
	int vLines;

	std::vector<unsigned int> indices;
	std::vector<unsigned int> lineIndices;
	std::vector<float> interleavedVertices;


	void Draw(Camera* camera, std::vector<Light*> lights) {
		//std::cout << "SPHERE: Rendering...\n";
		Shader* shader = ResourceManager::GetShader("lightingShader");

		shader->Use();

		shader->SetVector3f("baseColor", _color);
		shader->SetVector3f("viewPos", camera->Position);

		shader->SetInteger("material.diffuse", 0);
		shader->SetInteger("material.specular", 1);
		shader->SetFloat("material.shininess", 64.0f);

		shader->SetVector3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
		shader->SetVector3f("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		shader->SetVector3f("dirLight.diffuse", 0.8f, 0.8f, 0.8f);
		shader->SetVector3f("dirLight.specular", 0.5f, 0.5f, 0.5f);

		shader->SetVector3f("pointLights[0].position", lights[0]->_position);
		shader->SetVector3f("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		shader->SetVector3f("pointLights[0].diffuse", lights[0]->_color);
		shader->SetVector3f("pointLights[0].specular", lights[0]->_color);
		shader->SetFloat("pointLights[0].constant", 1.0f);
		shader->SetFloat("pointLights[0].linear", 0.09);
		shader->SetFloat("pointLights[0].quadratic", 0.032);

		shader->SetVector3f("pointLights[1].position", lights[1]->_position);
		shader->SetVector3f("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		shader->SetVector3f("pointLights[1].diffuse", lights[1]->_color);
		shader->SetVector3f("pointLights[1].specular", lights[1]->_color);
		shader->SetFloat("pointLights[1].constant", 1.0f);
		shader->SetFloat("pointLights[1].linear", 0.09);
		shader->SetFloat("pointLights[1].quadratic", 0.032);

		shader->SetVector3f("pointLights[2].position", lights[2]->_position);
		shader->SetVector3f("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		shader->SetVector3f("pointLights[2].diffuse", lights[2]->_color);
		shader->SetVector3f("pointLights[2].specular", lights[2]->_color);
		shader->SetFloat("pointLights[2].constant", 1.0f);
		shader->SetFloat("pointLights[2].linear", 0.09);
		shader->SetFloat("pointLights[2].quadratic", 0.032);

		shader->SetVector3f("pointLights[3].position", lights[3]->_position);
		shader->SetVector3f("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		shader->SetVector3f("pointLights[3].diffuse", lights[3]->_color);
		shader->SetVector3f("pointLights[3].specular", lights[3]->_color);
		shader->SetFloat("pointLights[3].constant", 1.0f);
		shader->SetFloat("pointLights[3].linear", 0.09);
		shader->SetFloat("pointLights[3].quadratic", 0.032);

		shader->SetVector3f("pointLights[4].position", lights[4]->_position);
		shader->SetVector3f("pointLights[4].ambient", 0.05f, 0.05f, 0.05f);
		shader->SetVector3f("pointLights[4].diffuse", lights[4]->_color);
		shader->SetVector3f("pointLights[4].specular", lights[4]->_color);
		shader->SetFloat("pointLights[4].constant", 1.0f);
		shader->SetFloat("pointLights[4].linear", 0.09);
		shader->SetFloat("pointLights[4].quadratic", 0.032);

		shader->SetVector3f("pointLights[5].position", lights[5]->_position);
		shader->SetVector3f("pointLights[5].ambient", 0.05f, 0.05f, 0.05f);
		shader->SetVector3f("pointLights[5].diffuse", lights[5]->_color);
		shader->SetVector3f("pointLights[5].specular", lights[5]->_color);
		shader->SetFloat("pointLights[5].constant", 1.0f);
		shader->SetFloat("pointLights[5].linear", 0.09);
		shader->SetFloat("pointLights[5].quadratic", 0.032);

		shader->SetMatrix4("projection", glm::perspective(glm::radians(45.0f), (float)1920 / (float)1080, 0.1f, 1000.0f));
		shader->SetMatrix4("view", camera->GetViewMatrix());
		glm::mat4 model = glm::mat4(1.0f);
		shader->SetMatrix4("model", model);

		Texture2D* diffuse = ResourceManager::GetTexture("marble");
		Texture2D* specular = ResourceManager::GetTexture("marble");


		glActiveTexture(GL_TEXTURE0);
		diffuse->Bind();

		glActiveTexture(GL_TEXTURE1);
		specular->Bind();

		last += 10.0f;

		model = glm::mat4(1.0f);
		model = glm::translate(model, _position);
		model = glm::rotate(model, glm::radians(last), glm::vec3(direction.z, -direction.y, -direction.x));
		shader->SetMatrix4("model", model);



		glBindVertexArray(_VAO);
		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);

		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);
	}

	/**
	 * Creates a Sphere at global position (x, y, z) with radius r
	 *
	*/
	Sphere(glm::vec3 position, float radius, bool Textured) {
		direction = glm::vec3(1.0f);
		std::cout << "SPHERE: Initializing...\n";
		_position = position;
		_color = glm::vec3(1.0f);
		this->radius = radius;
		this->textured = Textured;
		this->hLines = 100;
		this->vLines = 100;
		this->_VAO = 0;
		this->lineVAO = 0;
		//getVertices(); // get the array of vertices that define the sphere at Position
		//getIndicies(); // get the indices
		buildVerticesSmooth();
		setVAO();
		//setLineVao();

	}

	Sphere(glm::vec3 position, float radius, bool Textured, glm::vec3 color) {
		std::cout << "SPHERE: Initializing...\n";
		_position = position;
		_color = color;
		this->radius = radius;
		this->textured = Textured;
		this->hLines = 100;
		this->vLines = 100;
		this->_VAO = 0;
		this->lineVAO = 0;
		//getVertices(); // get the array of vertices that define the sphere at Position
		//getIndicies(); // get the indices
		buildVerticesSmooth();
		setVAO();
		//setLineVao();

	}

	void setVAO() {
		float* v = interleavedVertices.data();
		unsigned int* o = indices.data();

		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * interleavedVertices.size(), v, GL_STATIC_DRAW);

		unsigned int EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), o, GL_STATIC_DRAW);

		glBindVertexArray(VAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6));
		glEnableVertexAttribArray(2);

		this->_VAO = VAO;
	}

	void buildInterleavedVertices()
	{
		std::vector<float>().swap(interleavedVertices);

		std::size_t i, j;
		std::size_t count = vertices.size();
		for (i = 0, j = 0; i < count; i += 3, j += 2)
		{
			interleavedVertices.push_back(vertices[i]);
			interleavedVertices.push_back(vertices[i + 1]);
			interleavedVertices.push_back(vertices[i + 2]);

			interleavedVertices.push_back(normals[i]);
			interleavedVertices.push_back(normals[i + 1]);
			interleavedVertices.push_back(normals[i + 2]);

			interleavedVertices.push_back(texCoords[j]);
			interleavedVertices.push_back(texCoords[j + 1]);
		}
	}


	void buildVerticesSmooth()
	{
		const float PI = acos(-1);

		// clear memory of prev arrays

		unsigned int sectorCount = hLines;
		unsigned int stackCount = vLines;


		float x, y, z, xy;                              // vertex position
		float nx, ny, nz, lengthInv = 1.0f / radius;    // normal
		float s, t;                                     // texCoord

		float sectorStep = 2 * PI / sectorCount;
		float stackStep = PI / stackCount;
		float sectorAngle, stackAngle;

		for (int i = 0; i <= stackCount; ++i)
		{
			stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
			xy = radius * cosf(stackAngle);             // r * cos(u)
			z = radius * sinf(stackAngle);              // r * sin(u)

			// add (sectorCount+1) vertices per stack
			// the first and last vertices have same position and normal, but different tex coords
			for (int j = 0; j <= sectorCount; ++j)
			{
				sectorAngle = j * sectorStep;           // starting from 0 to 2pi

				// vertex position
				x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
				y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
				addVertex(x, y, z);

				// normalized vertex normal
				nx = x * lengthInv;
				ny = y * lengthInv;
				nz = z * lengthInv;
				addNormal(nx, ny, nz);

				// vertex tex coord between [0, 1]
				s = (float)j / sectorCount;
				t = (float)i / stackCount;
				addTexCoord(s, t);
			}
		}

		// indices
		//  k1--k1+1
		//  |  / |
		//  | /  |
		//  k2--k2+1
		unsigned int k1, k2;
		for (int i = 0; i < stackCount; ++i)
		{
			k1 = i * (sectorCount + 1);     // beginning of current stack
			k2 = k1 + sectorCount + 1;      // beginning of next stack

			for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
			{
				// 2 triangles per sector excluding 1st and last stacks
				if (i != 0)
				{
					addIndices(k1, k2, k1 + 1);   // k1---k2---k1+1
				}

				if (i != (stackCount - 1))
				{
					addIndices(k1 + 1, k2, k2 + 1); // k1+1---k2---k2+1
				}

				// vertical lines for all stacks
				lineIndices.push_back(k1);
				lineIndices.push_back(k2);
				if (i != 0)  // horizontal lines except 1st stack
				{
					lineIndices.push_back(k1);
					lineIndices.push_back(k1 + 1);
				}
			}
		}

		// generate interleaved vertex array as well
		buildInterleavedVertices();
	}

	///////////////////////////////////////////////////////////////////////////////
// add single vertex to array
///////////////////////////////////////////////////////////////////////////////
	void addVertex(float x, float y, float z)
	{
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);
	}



	///////////////////////////////////////////////////////////////////////////////
	// add single normal to array
	///////////////////////////////////////////////////////////////////////////////
	void addNormal(float nx, float ny, float nz)
	{
		normals.push_back(nx);
		normals.push_back(ny);
		normals.push_back(nz);
	}



	///////////////////////////////////////////////////////////////////////////////
	// add single texture coord to array
	///////////////////////////////////////////////////////////////////////////////
	void addTexCoord(float s, float t)
	{
		texCoords.push_back(s);
		texCoords.push_back(t);
	}

	void addIndices(unsigned int i1, unsigned int i2, unsigned int i3)
	{
		indices.push_back(i1);
		indices.push_back(i2);
		indices.push_back(i3);
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
	}

};