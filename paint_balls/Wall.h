#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>

#include "shader.h"
#include "resource_manager.h"
#include "Light.h"

class Wall {
public:
	bool debug = true;
	void Debug() {
		this->debug = !debug;
	}
	Wall(glm::vec3 position) {

		_position = position;

		float data[] = {
			// positions          // normals           // texture coords
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			 
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			 
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			 
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			 
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			 
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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

		_VAO = VAO;
	}
	virtual void Draw(Camera* camera, std::vector<Light*> lights) {
		Shader* shader = ResourceManager::GetShader("lightingShader");

		shader->Use();

		shader->SetVector3f("baseColor", glm::vec3(1.0f));
		shader->SetVector3f("viewPos", camera->Position);

		shader->SetInteger("material.diffuse", 0);
		shader->SetInteger("material.specular", 1);
		shader->SetFloat("material.shininess", 64.0f);

		shader->SetVector3f("dirLight.direction", 0.6f, -0.5f, 0.5f);
		shader->SetVector3f("dirLight.ambient", 0.025f, 0.025f, 0.07f);
		shader->SetVector3f("dirLight.diffuse", 0.4f, 0.4f, 0.85f);
		shader->SetVector3f("dirLight.specular", 0.25f, 0.25f, 0.6f);

		shader->SetVector3f("pointLights[0].position", lights[0]->_position);
		shader->SetVector3f("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		if (lights[0]->_destroyed) {
			shader->SetVector3f("pointLights[0].diffuse", glm::vec3(0.0f));
			shader->SetVector3f("pointLights[0].specular", glm::vec3(0.0f));
		}
		else {
			shader->SetVector3f("pointLights[0].diffuse", lights[0]->_color);
			shader->SetVector3f("pointLights[0].specular", lights[0]->_color);
		}
		shader->SetFloat("pointLights[0].constant", 1.0f);
		shader->SetFloat("pointLights[0].linear", 0.09);
		shader->SetFloat("pointLights[0].quadratic", 0.032);

		shader->SetVector3f("pointLights[1].position", lights[1]->_position);
		shader->SetVector3f("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		if (lights[1]->_destroyed) {
			shader->SetVector3f("pointLights[0].diffuse", glm::vec3(0.0f));
			shader->SetVector3f("pointLights[0].specular", glm::vec3(0.0f));
		}
		else {
			shader->SetVector3f("pointLights[0].diffuse", lights[1]->_color);
			shader->SetVector3f("pointLights[0].specular", lights[1]->_color);
		}
		shader->SetFloat("pointLights[1].constant", 1.0f);
		shader->SetFloat("pointLights[1].linear", 0.09);
		shader->SetFloat("pointLights[1].quadratic", 0.032);

		shader->SetVector3f("pointLights[2].position", lights[2]->_position);
		shader->SetVector3f("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		if (lights[2]->_destroyed) {
			shader->SetVector3f("pointLights[0].diffuse", glm::vec3(0.0f));
			shader->SetVector3f("pointLights[0].specular", glm::vec3(0.0f));
		}
		else {
			shader->SetVector3f("pointLights[0].diffuse", lights[2]->_color);
			shader->SetVector3f("pointLights[0].specular", lights[2]->_color);
		}
		shader->SetFloat("pointLights[2].constant", 1.0f);
		shader->SetFloat("pointLights[2].linear", 0.09);
		shader->SetFloat("pointLights[2].quadratic", 0.032);

		shader->SetVector3f("pointLights[3].position", lights[3]->_position);
		shader->SetVector3f("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		if (lights[3]->_destroyed) {
			shader->SetVector3f("pointLights[0].diffuse", glm::vec3(0.0f));
			shader->SetVector3f("pointLights[0].specular", glm::vec3(0.0f));
		}
		else {
			shader->SetVector3f("pointLights[0].diffuse", lights[3]->_color);
			shader->SetVector3f("pointLights[0].specular", lights[3]->_color);
		}
		shader->SetFloat("pointLights[3].constant", 1.0f);
		shader->SetFloat("pointLights[3].linear", 0.09);
		shader->SetFloat("pointLights[3].quadratic", 0.032);

		shader->SetVector3f("pointLights[4].position", lights[4]->_position);
		shader->SetVector3f("pointLights[4].ambient", 0.05f, 0.05f, 0.05f);
		if (lights[4]->_destroyed) {
			shader->SetVector3f("pointLights[0].diffuse", glm::vec3(0.0f));
			shader->SetVector3f("pointLights[0].specular", glm::vec3(0.0f));
		}
		else {
			shader->SetVector3f("pointLights[0].diffuse", lights[4]->_color);
			shader->SetVector3f("pointLights[0].specular", lights[4]->_color);
		}
		shader->SetFloat("pointLights[4].constant", 1.0f);
		shader->SetFloat("pointLights[4].linear", 0.09);
		shader->SetFloat("pointLights[4].quadratic", 0.032);

		shader->SetVector3f("pointLights[5].position", lights[5]->_position);
		shader->SetVector3f("pointLights[5].ambient", 0.05f, 0.05f, 0.05f);
		if (lights[5]->_destroyed) {
			shader->SetVector3f("pointLights[0].diffuse", glm::vec3(0.0f));
			shader->SetVector3f("pointLights[0].specular", glm::vec3(0.0f));
		}
		else {
			shader->SetVector3f("pointLights[0].diffuse", lights[5]->_color);
			shader->SetVector3f("pointLights[0].specular", lights[5]->_color);
		}
		shader->SetFloat("pointLights[5].constant", 1.0f);
		shader->SetFloat("pointLights[5].linear", 0.09);
		shader->SetFloat("pointLights[5].quadratic", 0.032);

		shader->SetMatrix4("projection", glm::perspective(glm::radians(45.0f), (float)1920 / (float)1080, 0.1f, 1000.0f));
		shader->SetMatrix4("view", camera->GetViewMatrix());
		glm::mat4 model = glm::mat4(1.0f);
		shader->SetMatrix4("model", model);

		Texture2D* diffuse = ResourceManager::GetTexture("brick_wall");
		Texture2D* specular = ResourceManager::GetTexture("brick_wall");


		glActiveTexture(GL_TEXTURE0);
		diffuse->Bind();

		glActiveTexture(GL_TEXTURE1);
		specular->Bind();


		model = glm::mat4(1.0f);
		shader->SetMatrix4("model", glm::translate(model, _position));

		

		glBindVertexArray(_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);
		
	}


	glm::vec3 _position;
protected:
	unsigned int _VAO;
	
};