#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>

#include "shader.h"
#include "resource_manager.h"
#include "Light.h"

class SkyBox {
public:
    unsigned int _VAO;

    SkyBox() {
        _VAO = 0;
    }


    void Draw(Camera* camera) {

        getVAO();

        Shader* shader = ResourceManager::GetShader("skybox");
        shader->Use();

        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content


        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera->GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1920 / (float)1080, 0.1f, 100.0f);

        view = glm::mat4(glm::mat3(camera->GetViewMatrix())); // remove translation from the view matrix
        shader->SetMatrix4("view", view);
        shader->SetMatrix4("projection", projection);
        // skybox cube
        glBindVertexArray(_VAO);

        Texture2D* diffuse = ResourceManager::GetTexture("skybox");
        Texture2D* specular = ResourceManager::GetTexture("skybox");


        glActiveTexture(GL_TEXTURE0);
        diffuse->Bind();

        glActiveTexture(GL_TEXTURE1);
        specular->Bind();

        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default
    }


    void getVAO() {
        float skyboxVertices[] = {
            // positions          
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
        };

        unsigned int skyboxVAO, skyboxVBO;
        glGenVertexArrays(1, &skyboxVAO);
        glGenBuffers(1, &skyboxVBO);

        glBindVertexArray(skyboxVAO);

        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        _VAO = skyboxVAO;
    }


};