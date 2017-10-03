#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <GL\glew.h>

class Shader {
public:
	GLuint Program;
	Shader(const GLchar* vertex_file_path, const GLchar* fragment_file_path);

	void Use();
};