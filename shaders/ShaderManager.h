#pragma once
#include "ShaderProgram.h"

class ShaderManager {
	//Each shader program is lazy loaded

public:
	enum ShaderProgramType {
		CONSTANT, LAMBERT, PHONG, SKYBOX, UI, count
	};

	ShaderManager();
	~ShaderManager();

	ShaderProgram* getShaderProgram(ShaderProgramType type);
	//ShaderProgram* getConstantShaderProgram();
	//ShaderProgram* getLambertShaderProgram();


private:
	struct ShaderProgramSource {
		ShaderProgram* shaderProgram;
		const char* vertexFilename;
		const char* fragmentFilename;
		bool usesLights;
	};


	ShaderProgramSource* shaderPrograms; //alternatively a map could be used instead of an array
};
