#pragma once
#include "Window.h"
#include "glm\matrix.hpp"
class Game {
public:
	Game(GLint width, GLint height, std::string title): m_window(width,height,title) {

	}
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Run() = 0;
protected:
	Window m_window;
};