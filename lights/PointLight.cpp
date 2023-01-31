#include "PointLight.h"

PointLight::PointLight(glm::vec3 pos,
	glm::vec4 ambientColor, glm::vec4 diffuseColor, glm::vec4 specularColor,
	float constAttenuation, float linearAttenuation, float quadraticAttenuation,
	bool enabled)
	: Light(ambientColor, diffuseColor, specularColor, enabled, Light::POINT_LIGHT_TYPE)
{
	this->pos = pos;
	this->constAttenuation = constAttenuation;
	this->linearAttenuation = linearAttenuation;
	this->quadraticAttenuation = quadraticAttenuation;

	this->posUN = nullptr;
	this->constAttUN = nullptr;
	this->linearAttUN = nullptr;
	this->quadraticAttUN = nullptr;
}

PointLight::~PointLight()
{
	delete[] posUN;
	delete[] constAttUN;
	delete[] linearAttUN;
	delete[] quadraticAttUN;
}

void PointLight::loadVarsToShaderProgram(ShaderProgram* shaderProgram)
{
	shaderProgram->setUniformVariable(posUN, pos);
	shaderProgram->setUniformVariable(constAttUN, constAttenuation);
	shaderProgram->setUniformVariable(linearAttUN, linearAttenuation);
	shaderProgram->setUniformVariable(quadraticAttUN, quadraticAttenuation);
}

void PointLight::setPos(glm::vec3 pos)
{
	this->pos = pos;
	setUniformVariableOfShaders(posUN, pos);
}

void PointLight::prepUniformNames()
{	
	this->posUN = getUniformName(posVarName);
	this->constAttUN = getUniformName(constAttVarName);
	this->linearAttUN = getUniformName(linearAttVarName);
	this->quadraticAttUN = getUniformName(quadraticAttVarName);
}
