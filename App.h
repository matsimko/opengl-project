#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>  

#include "Window.h"
#include <map>
#include "Scene.h"
#include "ShaderManager.h"
#include "ModelManager.h"

class App /*: WindowListener*/ {
private:
	Window* window;
	Scene* scene;
	App();
	bool isInit;
	ShaderManager* shaderManager;
	ModelManager* modelManager;

	std::map<GLFWwindow*, Window*> windowMap;
public:
	void init(WindowSettings windowSettings);
	void run();
	void quit();
	static App& getInstance();
	~App();
	void registerWindow(GLFWwindow *glfwWindow, Window *window);
	Window* getWindow(GLFWwindow* glfwWindow);
	//returns the "current" window
	Window* getWindow();
	Scene* getScene();

	void getCursorPos(double* x, double* y);
	void setCursorPos(double x, double y);

	ShaderManager* getShaderManager();
	ModelManager* getModelManager();

	//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	//prevent these from being used so that copies can't appear
	App(App const&) = delete;
	void operator=(App const&) = delete;

	static void error_callback(int error, const char* description);
};
