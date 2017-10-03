#pragma once
#include <vector>
#include "GL\glew.h"
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "Shader.h"

class Light {
public:
	Light();
	void Draw(Shader shader, glm::mat4 view, glm::mat4 projection);
	
	void Translate(glm::vec3 tranlation) {
		model = glm::translate(model, tranlation);
	}

	void Scale(glm::vec3 scale) {
		model = glm::scale(model, scale);
	}

	void Rotate(GLfloat radians, glm::vec3 direction) {
		model = glm::rotate(model, radians, direction);
	}
private:
	GLuint VAO;
	GLuint VBO;
	glm::mat4 model;
};