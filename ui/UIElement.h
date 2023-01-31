#pragma once
#include "ShaderProgram.h"

class UIElement {
public:
	virtual void draw(ShaderProgram* shaderProgram) = 0;
};
