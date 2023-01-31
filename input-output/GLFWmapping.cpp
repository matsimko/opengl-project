#include "GLFWmapping.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>  
#include "App.h"

InputState GLFWmapping::getInputState(int action)
{
	switch (action)
	{
	case GLFW_PRESS:
		return InputState::PRESSED;
	case GLFW_RELEASE:
		return InputState::RELEASED;
	default:
		return InputState::IGNORED;
	}
}
