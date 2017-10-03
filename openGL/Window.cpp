#include "Window.h"

Window::Window(GLint width, GLint height, std::string title) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	
	glfwGetFramebufferSize(m_window, &m_screenWidth, &m_screenHeight);

	if (m_window == nullptr) {
		std::cout << "Failed to create glfw window\r\n";
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window);
	glewExperimental = GLU_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initalize glew\r\n";
		return;
	}

	glfwSetKeyCallback(m_window, closeWindow);
}

Window::~Window(){
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool Window::WindowClosed(){
	return glfwWindowShouldClose(m_window);
}

GLFWwindow * Window::GetWindow(){
	return m_window;
}

void Window::BeginDraw(){
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::EndDraw(){
	glfwSwapBuffers(m_window);
}

void Window::GetScreenDimensions(int& width, int& height){
	width = m_screenWidth;
	height = m_screenHeight;
}

void Window::closeWindow(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window , true);
	}
}

void Window::SetWireFrame(bool b){
	if (b) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		m_wireFrame = true;
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		m_wireFrame = false;
	}
}

bool Window::GetWireFrame()
{
	return m_wireFrame;
}
