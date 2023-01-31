#include "Spotlight.h"

Spotlight::Spotlight(glm::vec3 pos, glm::vec3 dir, float cutOff, glm::vec4 ambientColor, glm::vec4 diffuseColor, glm::vec4 specularColor,
	float constAttenuation, float linearAttenuation, float quadraticAttenuation, bool enabled)
	: Light(ambientColor, diffuseColor, specularColor, enabled, Light::SPOTLIGHT_TYPE)
{
	this->pos = pos;
	this->dir = dir;
	this->cutOff = cutOff;

	this->constAttenuation = constAttenuation;
	this->linearAttenuation = linearAttenuation;
	this->quadraticAttenuation = quadraticAttenuation;

	this->dirUN = nullptr;
	this->posUN = nullptr;
	this->cutOffUN = nullptr;

	this->constAttUN = nullptr;
	this->linearAttUN = nullptr;
	this->quadraticAttUN = nullptr;

}

void Spotlight::loadVarsToShaderProgram(ShaderProgram* shaderProgram)
{
	shaderProgram->setUniformVariable(dirUN, dir);
	shaderProgram->setUniformVariable(posUN, pos);
	shaderProgram->setUniformVariable(cutOffUN, cutOff);

	shaderProgram->setUniformVariable(constAttUN, constAttenuation);
	shaderProgram->setUniformVariable(linearAttUN, linearAttenuation);
	shaderProgram->setUniformVariable(quadraticAttUN, quadraticAttenuation);
}

void Spotlight::prepUniformNames()
{
	this->dirUN = getUniformName(dirVarName);
	this->posUN = getUniformName(posVarName);
	this->cutOffUN = getUniformName(cutOffVarName);

	this->constAttUN = getUniformName(constAttVarName);
	this->linearAttUN = getUniformName(linearAttVarName);
	this->quadraticAttUN = getUniformName(quadraticAttVarName);
}


Spotlight::~Spotlight()
{
	delete[] dirUN;
	delete[] posUN;
	delete[] cutOffUN;

	delete[] constAttUN;
	delete[] linearAttUN;
	delete[] quadraticAttUN;
}

void Spotlight::setDir(glm::vec3 dir)
{
	this->dir = dir;
	setUniformVariableOfShaders(this->dirUN, dir);
}


void Spotlight::setPos(glm::vec3 pos)
{
	this->pos = pos;
	setUniformVariableOfShaders(this->posUN, pos);
}

glm::vec3 Spotlight::getPos()
{
	return pos;
}
