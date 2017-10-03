#pragma once
#include "Game.h"
#include "Shader.h"
#include "soil\SOIL.h"
#include "glm\matrix.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "Camera.h"
#include "assimp\Importer.hpp"
#include "Model.h"
#include "Terrain.h"
#include "Light.h"

static bool keys[1024];
class TestGame : public Game {
public:
	TestGame(GLint width, GLint height, std::string title);
	~TestGame();
	void Render();
	void Update();
	void Run();
private:
	Shader shader;
	Shader terrain;
	Shader lightShader;
	GLuint EBO;
	GLuint VAO;
	GLuint VBO;
	GLuint texture;
	GLuint texture2;
	int screenWidth, screenHeight;
	GLfloat deltaTime;
	GLfloat lastFrame;
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	Camera camera;
	double lastx;
	double lasty;
	Assimp::Importer importer;
	Model m_model;
	Model car;
	Terrain t;
	Light light;
};