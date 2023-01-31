#include "UI.h"
#include "App.h"
#include <glm/gtc/matrix_transform.hpp>

UI::UI()
{
	shaderProgram = App::getInstance().getShaderManager()->getShaderProgram(ShaderManager::UI);

	Window* window = App::getInstance().getWindow();
	onResize(window);

	window->addWindowListener(this);
}

void UI::render()
{
	glDepthMask(GL_FALSE); //might not be neccessary
	glStencilMask(0x00); //disable stencil buffer (otherwise stuff like the crosshair would overwrite the scene objects)
	shaderProgram->use();

	for (auto elem : elements) {
		elem->draw(shaderProgram);
	}
	glStencilMask(0xFF);
	glDepthMask(GL_TRUE);
}

void UI::addUIElement(UIElement* element)
{
	elements.push_back(element);
}

void UI::onResize(Window* window)
{
	float aspect = window->getAspectRatio();
	ortographicMatrix = glm::ortho(-aspect, aspect, -1.f, 1.f);
	shaderProgram->use();
	shaderProgram->setUniformVariable("ortographicMatrix", ortographicMatrix);
}
