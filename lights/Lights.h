#pragma once
#include "Light.h"

//manages lights for a Scene
class Lights {
private:
	static const int MAX_LIGHTS;
	static const char* lightCountUN;

	Light** lights;
	int nextIdx; //also represents the number of currently used lights

public:
	Lights();
	~Lights();
	void addLight(Light* light);
	void connectLightsToShaders(std::vector<ShaderProgram*> shaderPrograms);
};
