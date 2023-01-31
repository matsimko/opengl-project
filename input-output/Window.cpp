#include <GL/glew.h>
#include <GLFW/glfw3.h>  

#include <stdlib.h>
#include <stdio.h>

#include "Window.h"
#include "App.h"
#include "GLFWmapping.h"

Window::Window(WindowSettings settings) : inputHandler(), cursorHandler(), stencilObjectFinder(this)
{
	this->width = settings.width;
	this->height = settings.height;
	this->title = settings.title;
	this->cursorCaptured = false;

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	App::getInstance().registerWindow(window, this);

	// Set the callback functions of the created window to this class' methods
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);

	double cursorX, cursorY;
	getCursorPos(&cursorX, &cursorY);
	//set the initial cursor position to serve as the previous cursor position
	cursorHandler.setPrevCursorPos(cursorX, cursorY);

}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(window);
}

void Window::makeContextCurrent()
{
	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	float ratio = framebufferWidth / (float)framebufferHeight;
	glViewport(0, 0, framebufferWidth, framebufferHeight);
}

void Window::close()
{
	glfwSetWindowShouldClose(window, GL_TRUE);
}

Window::~Window()
{
	glfwDestroyWindow(window);
}

void Window::addInputListener(InputListener* listener)
{
	inputHandler.addListener(listener);
}

void Window::removeInputListener(InputListener* listener)
{
	inputHandler.removeListener(listener);
}

void Window::addCursorListener(CursorListener* listener)
{
	cursorHandler.addListener(listener);
}

void Window::removeCursorListener(CursorListener* listener)
{
	cursorHandler.removeListener(listener);
}


void Window::addWindowListener(WindowListener* listener)
{
	listeners.push_back(listener);
}

void Window::removeWindowListener(WindowListener* listener)
{
	listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
}

int Window::getHeight()
{
	return height;
}

int Window::getWidth()
{
	return width;
}

float Window::getAspectRatio()
{
	return width / (float) height;
}

glm::vec4 Window::getViewPort()
{
	return glm::vec4(0, 0, getWidth(), getHeight());
}

void Window::getCursorPos(double* x, double* y)
{
	if (!isCursorCaptured()) {
		glfwGetCursorPos(window, x, y);
	}
	else {
		getCenter(x, y);
	}
	
}

void Window::setCursorPos(double x, double y)
{
	glfwSetCursorPos(window, x, y);
}

void Window::captureCursor()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	cursorCaptured = true;
}

void Window::releaseCursor()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	cursorCaptured = false;
}

bool Window::isCursorCaptured()
{
	return cursorCaptured;
}

void Window::centerCursor()
{
	double x, y;
	getCenter(&x, &y);
	setCursorPos(x, y);
}

void Window::getCenter(double* x, double* y)
{
	*x = getWidth() / 2;
	*y = getHeight() / 2;
}

StencilObjectFinder& Window::getStencilObjectFinder()
{
	return stencilObjectFinder;
}


InputState Window::getStateOfInput(Input* input)
{
	if (input->getType() == InputType::MouseButton) {
		int state = glfwGetMouseButton(window, input->getKey());
		return GLFWmapping::getInputState(state);
	}
	else if (input->getType() == InputType::Key) {
		int state = glfwGetKey(window, input->getKey());
		return GLFWmapping::getInputState(state);
	}

	return InputState::IGNORED;
}



void Window::handleSizeChanged(int width, int height)
{
	this->width = width;
	this->height = height;
	glViewport(0, 0, width, height);

	for (auto listener : listeners) {
		listener->onResize(this);
	}
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//create the event and let the KeyHandler handle it 
	InputEvent e = { InputType::Key, key, GLFWmapping::getInputState(action) };
	App::getInstance().getWindow(window)->inputHandler.handle(e);

	
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}


void Window::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void Window::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void Window::window_size_callback(GLFWwindow* window, int width, int height) {
	App::getInstance().getWindow(window)->handleSizeChanged(width, height);
	printf("resize %d, %d \n", width, height);
}

void Window::cursor_callback(GLFWwindow* window, double x, double y) {
	//printf("cursor_callback \n");
	CursorEvent e = { x, y };
	App::getInstance().getWindow(window)->cursorHandler.handle(e);
}

void Window::button_callback(GLFWwindow* window, int button, int action, int mode) {
	//if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
	InputEvent e = { InputType::MouseButton, button, GLFWmapping::getInputState(action)};
	App::getInstance().getWindow(window)->inputHandler.handle(e);
}
