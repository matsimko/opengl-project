#include "StencilObjectFinder.h"
#include "Window.h"

StencilObjectFinder::StencilObjectFinder(Window* window)
{
	this->window = window;
}

IdentifiableObject* StencilObjectFinder::getObjectAtCursor()
{
	IdentifiableObject* obj = IdentifiableObject::getObjectById(getIdAtCursor());
	return obj;
}

GLuint StencilObjectFinder::getIdAtCursor()
{
	double cX, cY;
	window->getCursorPos(&cX, &cY);
	double x = cX;
	double y = window->getHeight() - cY;

	GLuint index;
	glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	return index;
}
