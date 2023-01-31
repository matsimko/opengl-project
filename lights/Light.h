#pragma once
#include "glm/vec4.hpp"
#include <vector>
#include "ShaderProgram.h"
#include "Light.h"

//class LightListener;

class Light {
private:
	int type;
	bool enabled;
	glm::vec4 ambientColor;
	glm::vec4 diffuseColor;
	glm::vec4 specularColor;

	//uniform names
	const char* typeUN;
	const char* enabledUN;
	const char* ambientUN;
	const char* diffuseUN;
	const char* specularUN;

	//If I used generic listener they would have to be able to somehow react separetely on the change of each variable,
	//e.g. by having methods for each of them (onPosChanged, onEnabledChanged ...)
	//To avoid this, I will use an array of ShaderPrograms,
	//because the light can tell the shader what to do instead of the shader asking the light for its data
	//std::vector<LightListener*> listeners;
	//void notifyPosChanged();
	std::vector<ShaderProgram*> shaderPrograms;

	int idx;
protected:

	virtual void loadVarsToShaderProgram(ShaderProgram *shaderProgram) = 0;
	virtual void prepUniformNames() = 0;
	void setUniformVariableOfShaders(const char* name, glm::vec3& vec);
	void setUniformVariableOfShaders(const char* name, glm::vec4& vec);
	void setUniformVariableOfShaders(const char* name, int num);

	char* getUniformName(const char* varName);

	static const int POINT_LIGHT_TYPE;
	static const int DIRECTIONAL_LIGHT_TYPE;
	static const int SPOTLIGHT_TYPE;

	static const char* lightsUniformName;
	//Light struct variables
	static const char* posVarName;
	static const char* ambientVarName;
	static const char* diffuseVarName;
	static const char* specularVarName;
	static const char* dirVarName;
	static const char* enabledVarName;
	static const char* cutOffVarName;
	static const char* quadraticAttVarName;
	static const char* linearAttVarName;
	static const char* constAttVarName;
	static const char* typeVarName;

public:
	Light(glm::vec4 ambientColor, glm::vec4 diffuseColor, glm::vec4 specularColor, bool enabled, int type);
	~Light();

	//void addListener(LightListener* listener);
	//void removeListener(LightListener* listener);

	//works also as a template method (calls loadVarsToShaderProgram) so that descendants can load additional uniform vars
	void addShaderProgram(ShaderProgram* shaderProgram);
	
	void setEnabled(bool enabled);

	//sets the Light's index and lets it create its uniform variable names (template method)
	void assignIndex(int idx);
};

