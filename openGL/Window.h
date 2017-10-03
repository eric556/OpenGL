#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window {
public:
	Window(GLint width, GLint height, std::string title);
	~Window();

	bool WindowClosed();
	GLFWwindow* GetWindow();
	void BeginDraw();
	void EndDraw();
	
	void GetScreenDimensions(int& width, int& height);

	void SetWireFrame(bool b);
	bool GetWireFrame();
private:
	GLFWwindow* m_window;
	int m_screenWidth;
	int m_screenHeight;
	bool m_wireFrame;

private:
	static void closeWindow(GLFWwindow * window, int key, int scancode, int action, int mods);
};