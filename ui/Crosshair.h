#pragma once
#include "UIElement.h"

#include "ModelWithPosition.h"

class Crosshair : public UIElement
{
private:
	Model* model;

	float thickness;
	float length;
	glm::vec4 color;

	void setUpVertices();
public:
	Crosshair(glm::vec4 color, float length,  float thickness);


	// Inherited via UIElement
	virtual void draw(ShaderProgram* shaderProgram) override;

};

