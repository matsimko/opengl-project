#pragma once
#include "Renderable.h"
#include "ShaderProgram.h"
#include "WindowListener.h"
#include <vector>
#include "UIElement.h"

class UI : public Renderable, public WindowListener
{
private:
	std::vector<UIElement*> elements;
	ShaderProgram* shaderProgram;

	glm::mat4 ortographicMatrix;
public:
	UI();

	// Inherited via Renderable
	virtual void render() override;

	void addUIElement(UIElement* element);

	// Inherited via WindowListener
	virtual void onResize(Window* window) override;
};

