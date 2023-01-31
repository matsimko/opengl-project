#define _CRT_SECURE_NO_WARNINGS

#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

void Shader::load()
{
	id = glCreateShader(type);
	glShaderSource(id, 1, &code, NULL);
	glCompileShader(id);

	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar* errorLog = new GLchar[maxLength];
		glGetShaderInfoLog(id, maxLength, &maxLength, errorLog);
		fprintf(stderr, "Compilation error: %s\n", errorLog);

		// Exit with failure.
		glDeleteShader(id); // Don't leak the shader.
		delete[] errorLog;
		exit(1);
	}
}

std::string Shader::loadFile(const char* filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cout << "Unable to open file " << filename << std::endl;
	}
	std::stringstream fileData;
	fileData << file.rdbuf();
	file.close();
	return fileData.str();
}

Shader::Shader(GLenum type)
{
	code = nullptr;
	id = 0;
	this->type = type;
}

Shader::~Shader()
{
	delete[] code;
}

void Shader::loadFromString(const char* code)
{
	this->code = new char[strlen(code) + 1];
	strcpy(this->code, code);
	load();
}

void Shader::loadFromFile(const char* filename)
{
	std::string codeStr = loadFile(filename);
	this->code = new char[codeStr.size() + 1];
	strcpy(this->code, codeStr.c_str());
	load();
}

GLuint Shader::getId()
{
	return id;
}
