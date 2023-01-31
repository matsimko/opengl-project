#pragma once
#include "Light.h"
#include "glm/vec3.hpp"

class Spotlight : public Light {
private:
	glm::vec3 dir;
	glm::vec3 pos;
	float cutOff;

	float constAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;

	const char* dirUN;
	const char* posUN;
	const char* cutOffUN;

	const char* constAttUN;
	const char* linearAttUN;
	const char* quadraticAttUN;
protected:
	// Inherited via Light
	virtual void loadVarsToShaderProgram(ShaderProgram* shaderProgram) override;
	virtual void prepUniformNames() override;

public:
	Spotlight(glm::vec3 pos = glm::vec3(0, 0, 0),
		glm::vec3 dir = glm::vec3(0.f, -1.f, 0), 
		float cutOff = 0.87,
		glm::vec4 ambientColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f),
		glm::vec4 diffuseColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4 specularColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		float constAttenuation = 1.f, float linearAttenuation = 0.045f, float quadraticAttenuation = 0.0075f,
		bool enabled = true);
	~Spotlight();

	void setDir(glm::vec3 dir);
	void setPos(glm::vec3 pos);
	glm::vec3 getPos();


};
