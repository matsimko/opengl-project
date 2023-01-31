#include "Lights.h"

const int Lights::MAX_LIGHTS = 10;
const char* Lights::lightCountUN = "lightCount";

Lights::Lights()
{
	this->nextIdx = 0;
	lights = new Light * [MAX_LIGHTS];
	for (int i = 0; i < MAX_LIGHTS; i++) {
		lights[i] = nullptr;
	}
}

Lights::~Lights()
{
	for (int i = 0; i < MAX_LIGHTS; i++) {
		delete lights[i];
	}
	delete[] lights;
}

void Lights::addLight(Light* light)
{
	if (this->nextIdx >= MAX_LIGHTS) {
		throw std::exception("The new light would exceed the maximum number of lights.");
	}
	light->assignIndex(this->nextIdx);
	lights[this->nextIdx] = light;
	this->nextIdx++;
}

void Lights::connectLightsToShaders(std::vector<ShaderProgram*> shaderPrograms)
{
	for (auto shaderProgram : shaderPrograms) {
		if (shaderProgram->isUsingLights()) {
			shaderProgram->use();
			shaderProgram->setUniformVariable(lightCountUN, this->nextIdx);
			for (int i = 0; i < nextIdx; i++) {
				lights[i]->addShaderProgram(shaderProgram);
			}
		}
	}
}
