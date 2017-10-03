#pragma once
#pragma once
// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
// GL Includes
#include <GL/glew.h> 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Shader.h" 
#include "assimp\types.h"
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	GLuint id;
	string type;
	aiString path;
};

class Mesh {
public:
	vector<Vertex> verticies;
	vector<GLuint>indices;
	vector<Texture> textures;
	Mesh(vector<Vertex> verticies, vector<GLuint> indices, vector<Texture> textures) {
		this->verticies = verticies;
		this->indices = indices;
		this->textures = textures;
	
		this->setupMesh();
	}

	void Draw(Shader shader);
private:
	GLuint VAO, VBO, EBO;
	void setupMesh();
};