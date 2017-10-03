#pragma once
#include <vector>
#include "GL\glew.h"
#include "glm\glm.hpp"
#include "Shader.h"

struct Quad {
	glm::vec3 corners[4];
};

struct Triangle {
	glm::vec3 corners[3];
	glm::vec3 normal;
};

class Terrain {
public:
	std::vector<std::vector<glm::vec3>> verticies;
	std::vector<Quad> quads;
	std::vector<Triangle> triangles;
	std::vector <GLuint> indicies;
	std::vector<std::vector<glm::vec3>> normals;
	int width;
	int height;
	int vertCount;
	void SetupMesh(std::string path, float xOffset, float yOffset, float zOffset) {
		int channels;
		unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, 1);
		if (image) {
			std::cout << "Image loaded\n";
			std::cout << "Width: " << width << "\n";
			std::cout << "Height: " << height << "\n";
			for (int z = 0; z < height; z++) {
				std::vector<glm::vec3> temp;
				for (int x = 0; x < width; x++) {
					glm::vec3 vertex;
					vertex.x = ((GLfloat)x) * xOffset;
					vertex.z = ((GLfloat)z) * zOffset;
					vertex.y = ((GLfloat)image[(z * width) + x]) * yOffset;
					temp.push_back(vertex);
				}
				verticies.push_back(temp);
			}
		}


		

		GenerateQuads();
		std::cout << "Size of quads: " << quads.size() << "\n";
		GenerateTriangles();
		std::cout << "Triangles size: " << triangles.size() << "\n";
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		std::vector<GLfloat> vert;
		for each(Triangle triangle in triangles) {
			for (int i = 0; i < 3; i++) {
				vert.push_back(triangle.corners[i].x);
				vert.push_back(triangle.corners[i].y);
				vert.push_back(triangle.corners[i].z);
				//std::cout << "Normal: " << triangle.normal.x <<", " << triangle.normal.y << ", "<< triangle.normal.z << "\n";
				vert.push_back(0);
				vert.push_back(0);
				vert.push_back(0);
			}
		}
		std::cout << "Final vert count: " << vert.size()  <<"\n";
		vertCount = vert.size();
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(GLfloat), &vert[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),(GLvoid*)3);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}

	void GenerateQuads() {
		for (int i = 0; i < height-1; i++) {
			for (int j = 0; j < width - 1; j++) {
				Quad q;
				q.corners[0] = verticies[j][i];
				q.corners[1] = verticies[j + 1][i];
				q.corners[2] = verticies[j + 1][i + 1];
				q.corners[3] = verticies[j][i + 1];
				quads.push_back(q);
			}
		}
	}

	void GenerateTriangles() {
		for each (Quad quad in quads)
		{
			Triangle t1;
			Triangle t2;

			t1.corners[0] = quad.corners[0];
			t1.corners[1] = quad.corners[1];
			t1.corners[2] = quad.corners[2];

			glm::vec3 U = t1.corners[1] - t1.corners[0];
			glm::vec3 V = t1.corners[2] - t1.corners[0];

			t1.normal = glm::cross(U, V);
			t1.normal = glm::normalize(t1.normal);

			t2.corners[0] = quad.corners[0];
			t2.corners[1] = quad.corners[2];
			t2.corners[2] = quad.corners[3];

			U = t2.corners[1] - t2.corners[0];
			V = t2.corners[2] - t2.corners[0];
			
			t2.normal = glm::cross(U, V);
			t2.normal = glm::normalize(t2.normal);

			//std::cout << "T1 normal: " << t1.normal.x << ", " << t1.normal.y << ", " << t1.normal.z << "\n";
			triangles.push_back(t1);
			triangles.push_back(t2);
		}
	}

	void GenerateIndicies() {

	}

	void Draw(Shader shader, glm::mat4 view, glm::mat4 projection) {
		shader.Use();
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(this->model));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);
		glBindVertexArray(0);
		model = glm::mat4();
	}

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
	GLuint VBO;
	GLuint VAO;
	glm::mat4 model;
};
