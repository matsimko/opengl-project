#pragma once
#include "IdentifiableObject.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>  

class Window;

class StencilObjectFinder {
private:
	Window* window;

public:
	StencilObjectFinder(Window *window);

	IdentifiableObject* getObjectAtCursor();
	GLuint getIdAtCursor();
};
