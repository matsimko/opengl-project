#include "Scene.h"
#include "App.h"
#include <algorithm>
#include <glm/vec3.hpp>
#include <glm/ext/matrix_projection.hpp>
#include "Controls.h"

Scene::Scene() : app(App::getInstance())
{
	camera = new Camera(App::getInstance().getWindow()->getAspectRatio());
	lights = new Lights();
	background = nullptr;
	ui = new UI();
	controls = nullptr;
}

void Scene:: addRenderable(Renderable* renderable)
{
	renderables.push_back(renderable);
}

void Scene::removeRenderable(Renderable* renderable)
{
	renderables.erase(std::remove(renderables.begin(), renderables.end(), renderable), renderables.end());
}

void Scene::addUpdatable(Updatable* updatable)
{
	updatables.push_back(updatable);
}

void Scene::removeUpdatable(Updatable* updatable)
{
	updatables.erase(std::remove(updatables.begin(), updatables.end(), updatable), updatables.end());
}

void Scene::addRenderableModel(RenderableModel* renderableModel)
{
	addRenderable(renderableModel);
	addUpdatable(renderableModel);
}

void Scene::removeRenderableModel(RenderableModel* renderableModel)
{
	removeRenderable(renderableModel);
	removeUpdatable(renderableModel);
}

void Scene::addShaderProgram(ShaderProgram* shaderProgram)
{
	shaderPrograms.push_back(shaderProgram);
	camera->addListener(shaderProgram);
}

void Scene::setBackground(Background* background)
{
	this->background = background;
	camera->addListener(background);
}

void Scene::setControls(Controls* controls)
{
	Window* window = App::getInstance().getWindow();
	if (this->controls != nullptr) {
		window->removeInputListener(this->controls);
	}
	this->controls = controls;
	window->addInputListener(this->controls);
}



void Scene::render()
{
	//render bg first 
	//(another option is to have a bg wrapper that will be put at the start of renderables
	//and when subclasses call setBackground it will set the bg inside the wrapper)
	if (background != nullptr) {
		background->render();
	}
	for (auto renderable : renderables) {
		renderable->render();
	}
	ui->render();
}

void Scene::load()
{
	//register camera to window so it can react on resize
	app.getWindow()->addWindowListener(camera);

	doLoad();

	camera->notify(); //notify listeners about initial settings
	lights->connectLightsToShaders(shaderPrograms);
}

Camera* Scene::getCamera()
{
	return camera;
}

Scene::~Scene()
{
	for (auto renderable : renderables) {
		delete renderable;
	}
	delete camera;
	delete lights;
	delete background;
	delete ui;
	delete controls;
}

void Scene::update(double dt)
{
	for (auto updatable : updatables) {
		updatable->update(dt);
	}
}

glm::vec3 Scene::getWorldSpacePosAtCursor()
{
	Window* window = app.getWindow();

	double cX, cY;
	window->getCursorPos(&cX, &cY);

	double x = cX;
	double y = window->getHeight() - cY;

	//GLbyte color[4];
	GLfloat depth;
	GLuint index;
	//glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	glm::vec3 screenPos = glm::vec3(x, y, depth);
	glm::vec4 viewPort = window->getViewPort();
	glm::vec3 pos = glm::unProject(screenPos, camera->getViewMatrix(), camera->getProjectionMatrix(), viewPort);

	return pos;
}

Controls* Scene::getControls()
{
	return controls;
}
