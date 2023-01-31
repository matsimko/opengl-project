#include "App.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/trigonometric.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "ShaderProgram.h"
#include "SceneFactory.h"
#include "Texture.h"

App::App()
{
	this->window = nullptr;
	this->scene = nullptr;
	this->isInit = false;
	this->shaderManager = nullptr;
	this->modelManager = nullptr;
}

void App::init(WindowSettings windowSettings)
{
	if (isInit) {
		return;
	}
	isInit = true;

	glfwSetErrorCallback(App::error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//inicializace konkretni verze
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
		GLFW_OPENGL_CORE_PROFILE);*/

	window = new Window(windowSettings);
	window->makeContextCurrent();
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	//Enable Z-buffering
	glEnable(GL_DEPTH_TEST);

	//Enabled Stencil buffer
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	//create shader manager
	shaderManager = new ShaderManager();

	//create model manager
	modelManager = new ModelManager();

	//create and load scene
	SceneFactory& sceneFactory = SceneFactory::getInstance();
	scene = sceneFactory.newScene();
	scene->load();

}

void App::run()
{
	double t = glfwGetTime();
	double dt;

	while (!window->shouldClose())
	{
		dt = glfwGetTime() - t;
		t += dt;

		// clear color, depth and stencil buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		scene->update(dt);
		scene->render();

		// checks if any events are triggered (like keyboard input)
		// and calls the corresponding functions (which were registered via callback methods)
		glfwPollEvents();
		// put the stuff we�ve been drawing onto the display
		window->swapBuffers();

		glfwPollEvents();
	}
}

void App::quit()
{
	window->close();
}

App& App::getInstance()
{
	static App instance;
	return instance;
}

App::~App()
{
	delete shaderManager;
	delete window;
	delete scene;
	Texture::deleteTextures(); 
	delete modelManager;
	
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void App::registerWindow(GLFWwindow* glfwWindow, Window* window)
{
	windowMap[glfwWindow] = window;
}

Window* App::getWindow(GLFWwindow* glfwWindow)
{
	return windowMap[glfwWindow];
}

Window* App::getWindow()
{
	return window;
}

Scene* App::getScene()
{
	return scene;
}

void App::getCursorPos(double* x, double* y)
{
	window->getCursorPos(x, y);
}

void App::setCursorPos(double x, double y)
{
	window->setCursorPos(x, y);
}

ShaderManager* App::getShaderManager()
{
	return shaderManager;
}

ModelManager* App::getModelManager()
{
	return modelManager;
}

void App::error_callback(int error, const char* description) { fputs(description, stderr); }