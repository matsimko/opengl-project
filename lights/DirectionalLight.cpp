#include "DirectionalLight.h"

void DirectionalLight::loadVarsToShaderProgram(ShaderProgram* shaderProgram)
{
	shaderProgram->setUniformVariable(dirUN, dir);
}

void DirectionalLight::prepUniformNames()
{
	this->dirUN = getUniformName(dirVarName);
}

DirectionalLight::DirectionalLight(glm::vec3 dir, glm::vec4 ambientColor, glm::vec4 diffuseColor, glm::vec4 specularColor, bool enabled)
	: Light(ambientColor, diffuseColor, specularColor, enabled, Light::DIRECTIONAL_LIGHT_TYPE)
{
	this->dir = dir;

	this->dirUN = nullptr;
}
DirectionalLight::~DirectionalLight()
{
	delete[] dirUN;
}

void DirectionalLight::setDir(glm::vec3 dir)
{
	this->dir = dir;
	setUniformVariableOfShaders(this->dirUN, dir);
}
