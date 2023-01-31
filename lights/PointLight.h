#pragma once
#include "Light.h"
#include "glm/vec3.hpp"

class PointLight : public Light {
private:
	glm::vec3 pos;
	float constAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;

	const char* posUN;
	const char* constAttUN;
	const char* linearAttUN;
	const char* quadraticAttUN;

protected:
	// Inherited via Light
	virtual void loadVarsToShaderProgram(ShaderProgram* shaderProgram) override;
	virtual void prepUniformNames() override;

public:
	PointLight(glm::vec3 pos = glm::vec3(0,0,0),
		glm::vec4 ambientColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f),
		glm::vec4 diffuseColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4 specularColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		float constAttenuation = 1.f, float linearAttenuation = 0.045f, float quadraticAttenuation = 0.0075f,
		bool enabled = true);
	~PointLight();

	void setPos(glm::vec3 pos);


};
