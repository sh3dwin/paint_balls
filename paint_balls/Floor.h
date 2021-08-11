#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>

#include "shader.h"
#include "GameObject.h"
#include "resource_manager.h"
#include "Light.h"

class Floor {
public:
	glm::vec3 _position;
	unsigned int _VAO;

	Floor(glm::vec3 position){
		_position = position;
		float data[] = {
			-100.f,  0.f, -100.f,  0.0f,  1.0f,  0.0f,  0.0f,   400.0f,
			 100.f,  0.f, -100.f,  0.0f,  1.0f,  0.0f,  400.0f, 400.0f,
			 100.f,  0.f,  100.f,  0.0f,  1.0f,  0.0f,  400.0f, 0.0f,
			 100.f,  0.f,  100.f,  0.0f,  1.0f,  0.0f,  400.0f, 0.0f,
			-100.f,  0.f,  100.f,  0.0f,  1.0f,  0.0f,  0.0f,   0.0f,
			-100.f,  0.f, -100.f,  0.0f,  1.0f,  0.0f,  0.0f,   400.0f
		};

		unsigned int VAO, VBO;
		glGenVertexArrays(1, &VAO);

		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);


		glBindVertexArray(VAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		this->_VAO = VAO;
	}

	void Draw(Camera* camera, std::vector<Light*> lights) {
		Shader* shader = ResourceManager::GetShader("lightingShader");

		shader->Use();

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

		shader->SetMatrix4("projection", glm::perspective(glm::radians(45.0f), (float)1920 / (float)1080, 0.1f, 1000.0f));
		shader->SetMatrix4("view", camera->GetViewMatrix());

		glm::mat4 model = glm::mat4(1.0f);
		shader->SetMatrix4("model", model);

		Texture2D* diffuse = ResourceManager::GetTexture("tile_diffuse");
		Texture2D* specular = ResourceManager::GetTexture("tile_specular");


		glActiveTexture(GL_TEXTURE0);
		diffuse->Bind();

		glActiveTexture(GL_TEXTURE1);
		specular->Bind();


		model = glm::mat4(1.0f);
		
		//model = glm::scale(model, glm::vec3(100.f, 1.f, 100.f));
		shader->SetMatrix4("model", glm::translate(model, _position));



		glBindVertexArray(_VAO);

		std::cout << "FLOOR: Rendering...\n";

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);
	}
};