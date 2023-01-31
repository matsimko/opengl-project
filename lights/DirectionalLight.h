#pragma once
#include "Light.h"
#include "glm/vec3.hpp"

class DirectionalLight : public Light {
private:
	glm::vec3 dir;

	const char* dirUN;
protected:
	// Inherited via Light
	virtual void loadVarsToShaderProgram(ShaderProgram* shaderProgram) override;
	virtual void prepUniformNames() override;

public:
	DirectionalLight(glm::vec3 dir = glm::vec3(2.f, -1.f, 0), //it's normalized in the shader anyway
		glm::vec4 ambientColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f),
		glm::vec4 diffuseColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4 specularColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		bool enabled = true);
	~DirectionalLight();

	void setDir(glm::vec3 dir);


};
