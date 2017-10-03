#pragma once
#include "TestGame.h"

TestGame::TestGame(GLint width, GLint height, std::string title) :
	Game(width, height, title), shader("SimpleVertexShader.vert", "SimpleFragmentShader.frag"),
	terrain("TerrainShader.vert", "TerrainShader.frag"),
	m_model("C:/Users/nowace/Documents/Visual Studio 2015/Projects/openGL/openGL/Models/nanosuit/nanosuit.obj"), 
	car("C:/Users/nowace/Documents/Visual Studio 2015/Projects/openGL/openGL/Models/turbosonic3ds/turbosonic.3DS"),
	lightShader("LightShader.vert","LightShader.frag"){
	glfwSetKeyCallback(m_window.GetWindow(), key_callback);
	//glfwSetInputMode(m_window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	//glBindVertexArray(VertexArrayID);
	m_window.GetScreenDimensions(screenWidth, screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);
	t.SetupMesh("terrain2.jpg",2,0.2,2);
	deltaTime = 0.0f;
	lastFrame = 0.0f;
	glfwGetCursorPos(m_window.GetWindow(), &lastx, &lasty);
	
	
	
	m_window.SetWireFrame(false);
}

TestGame::~TestGame(){
}

void TestGame::Render(){
	m_window.BeginDraw();
	glm::mat4 view;
	glm::mat4 projection;

	view = camera.GetViewMatrix();
	projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
	glm::vec3 lightPos = glm::vec3(10.0f, 10.0f, 10.0f);
	light.Translate(lightPos);
	//light.Scale(glm::vec3(1.0f));
	light.Draw(lightShader, view, projection);
	
	shader.Use();
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	model = glm::rotate(model, (GLfloat)glfwGetTime() * glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	
	GLint lightColorLoc = glGetUniformLocation(shader.Program, "lightColor");
	GLint lightPosLoc = glGetUniformLocation(shader.Program, "lightPos");
	GLint viewPosLoc = glGetUniformLocation(shader.Program, "viewPos");
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);
	m_model.Draw(shader);

	terrain.Use();
	glUniformMatrix4fv(glGetUniformLocation(terrain.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(terrain.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

	lightColorLoc = glGetUniformLocation(terrain.Program, "lightColor");
	lightPosLoc = glGetUniformLocation(terrain.Program, "lightPos");
	viewPosLoc = glGetUniformLocation(terrain.Program, "viewPos");
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);
	t.Translate(glm::vec3(0.0f, -1.75f, 0.0f));
	t.Scale(glm::vec3(0.1f, 0.1f, 0.1f));
	t.Draw(terrain, view, projection);
	m_window.EndDraw();
}

void TestGame::Update(){
	glfwPollEvents();
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	if (keys[GLFW_KEY_W]) {
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (keys[GLFW_KEY_S]) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (keys[GLFW_KEY_D]) {
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
	if (keys[GLFW_KEY_A]) {
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (keys[GLFW_KEY_F]) {
		m_window.SetWireFrame(!m_window.GetWireFrame());
	}
	double xpos, ypos;
	glfwGetCursorPos(m_window.GetWindow(), &xpos, &ypos);
	camera.ProcessMouseMovement(xpos - lastx, lasty - ypos);
	lastx = xpos;
	lasty = ypos;
}

void TestGame::Run(){
	while (!m_window.WindowClosed()) {
		Update();
		Render();
	}
	
	glfwTerminate();
}

void TestGame::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}
