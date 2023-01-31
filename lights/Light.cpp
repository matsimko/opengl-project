#define _CRT_SECURE_NO_WARNINGS

#include "Light.h"
#include "LightListener.h"
#include <string>
#include <stdexcept>
#include <exception>


const int Light::POINT_LIGHT_TYPE = 1;
const int Light::DIRECTIONAL_LIGHT_TYPE = 2;
const int Light::SPOTLIGHT_TYPE = 3;

const char* Light::lightsUniformName = "lights";
//Light struct variables
const char* Light::posVarName = "pos";
const char* Light::ambientVarName = "ambientColor";
const char* Light::diffuseVarName = "diffuseColor";
const char* Light::specularVarName = "specularColor";
const char* Light::dirVarName = "direction";
const char* Light::enabledVarName = "enabled";
const char* Light::cutOffVarName = "cutOff";
const char* Light::quadraticAttVarName = "quadraticAttenuation";
const char* Light::linearAttVarName = "linearAttenuation";
const char* Light::constAttVarName = "constAttenuation";
const char* Light::typeVarName = "type";


void Light::setUniformVariableOfShaders(const char* name, glm::vec3& vec)
{
	for (auto shaderProgram : shaderPrograms) {
		shaderProgram->use();
		shaderProgram->setUniformVariable(name, vec);
	}
}

void Light::setUniformVariableOfShaders(const char* name, glm::vec4& vec)
{
	for (auto shaderProgram : shaderPrograms) {
		shaderProgram->use();
		shaderProgram->setUniformVariable(name, vec);
	}
}

void Light::setUniformVariableOfShaders(const char* name, int num)
{
	for (auto shaderProgram : shaderPrograms) {
		shaderProgram->use();
		shaderProgram->setUniformVariable(name, num);
	}
}

char* Light::getUniformName(const char* varName)
{
	char buff[255];
	sprintf(buff, "%s[%d].%s", lightsUniformName, idx, varName);
	char* result = new char[strlen(buff) + 1];
	strcpy(result, buff);
	return result;
}


Light::Light(glm::vec4 ambientColor, glm::vec4 diffuseColor, glm::vec4 specularColor, bool enabled, int type)
{
	this->enabled = enabled;
	this->ambientColor = ambientColor;
	this->diffuseColor = diffuseColor;
	this->specularColor = specularColor;
	this->type = type;

	idx = -1;
	typeUN = enabledUN = ambientUN = diffuseUN = specularUN = nullptr;
}

Light::~Light()
{
	delete[] typeUN;
	delete[] enabledUN;
	delete[] ambientUN;
	delete[] diffuseUN;
	delete[] specularUN;
}


void Light::addShaderProgram(ShaderProgram* shaderProgram)
{
	shaderPrograms.push_back(shaderProgram);
	//load the current state of the light into it
	shaderProgram->use();
	shaderProgram->setUniformVariable(typeUN, type);
	shaderProgram->setUniformVariable(enabledUN, enabled);
	shaderProgram->setUniformVariable(diffuseUN, diffuseColor);
	shaderProgram->setUniformVariable(specularUN, specularColor);
	shaderProgram->setUniformVariable(ambientUN, ambientColor);
	//let the subclass load its own variables
	loadVarsToShaderProgram(shaderProgram);
}

void Light::setEnabled(bool enabled)
{
	this->enabled = enabled;
	setUniformVariableOfShaders(enabledUN, enabled);
}

void Light::assignIndex(int idx)
{
	this->idx = idx;
	this->typeUN = getUniformName(typeVarName);
	this->enabledUN = getUniformName(enabledVarName);
	this->ambientUN = getUniformName(ambientVarName);
	this->diffuseUN = getUniformName(diffuseVarName);
	this->specularUN = getUniformName(specularVarName);
	//let the subclass prep its own uniform names
	prepUniformNames();
}



/*void Light::addListener(LightListener* listener)
{
	listeners.push_back(listener);
}*/
