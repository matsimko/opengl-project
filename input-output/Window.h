#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>  
#include "glm/vec4.hpp"

#include "InputHandler.h"
#include "WindowListener.h"
#include "CursorHandler.h"
#include "StencilObjectFinder.h"
#include "InputState.h"

struct WindowSettings {
	int width;
	int height;
	const char* title;
};

class Window {

public:
	Window(WindowSettings settings);
	bool shouldClose();
	void swapBuffers();
	// makes the OpenGL context of the window current, and sets the OpenGL viewport
	void makeContextCurrent();
	void close();
	~Window();

	void addInputListener(InputListener* listener);
	void removeInputListener(InputListener* listener);

	void addCursorListener(CursorListener* listener);
	void removeCursorListener(CursorListener* listener);

	void addWindowListener(WindowListener* listener);
	void removeWindowListener(WindowListener* listener);

	int getHeight();
	int getWidth();
	float getAspectRatio();
	glm::vec4 getViewPort();

	//if the cursor is captured, the center of the screen is returned
	void getCursorPos(double* x, double* y);

	void setCursorPos(double x, double y);
	void captureCursor();
	void releaseCursor();
	bool isCursorCaptured();
	void centerCursor();
	void getCenter(double *x, double *y);

	StencilObjectFinder& getStencilObjectFinder();

	InputState getStateOfInput(Input* input);


private:
	GLFWwindow* window;
	int width;
	int height;
	const char* title;
	bool cursorCaptured;

	int framebufferWidth;
	int framebufferHeight;

	InputHandler inputHandler;
	CursorHandler cursorHandler;
	StencilObjectFinder stencilObjectFinder;
	
	std::vector<WindowListener*> listeners;
	void handleSizeChanged(int width, int height);

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void window_focus_callback(GLFWwindow* window, int focused);

	static void window_iconify_callback(GLFWwindow* window, int iconified);

	static void window_size_callback(GLFWwindow* window, int width, int height);

	static void cursor_callback(GLFWwindow* window, double x, double y);

	static void button_callback(GLFWwindow* window, int button, int action, int mode);


};

