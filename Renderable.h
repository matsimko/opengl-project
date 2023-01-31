#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Renderable {
public:
	virtual void render() = 0;
	virtual GLuint getId();
};
