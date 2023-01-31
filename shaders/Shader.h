#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>  
#include <string>

class Shader {
private:
	GLuint id;
	GLenum type;
	char* code;
	void load();
	std::string loadFile(const char* filename);

public:
	

	Shader(GLenum type);
	~Shader();

	void loadFromString(const char* code);
	void loadFromFile(const char* filename);
	GLuint getId();
};
