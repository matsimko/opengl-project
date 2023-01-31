#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
	shaderPrograms = new ShaderProgramSource[count];
	shaderPrograms[CONSTANT] = { nullptr, "ConstantVertexShader.glsl", "ConstantFragmentShader.glsl", false };
	shaderPrograms[LAMBERT] = { nullptr, "LambertVertexShader.glsl", "LambertFragmentShader.glsl", true };
	shaderPrograms[PHONG] = { nullptr, "PhongVertexShader.glsl", "PhongFragmentShader.glsl", true };
	shaderPrograms[SKYBOX] = { nullptr, "SkyboxVertexShader.glsl", "SkyboxFragmentShader.glsl", false };
	shaderPrograms[UI] = { nullptr, "UIVertexShader.glsl", "UIFragmentShader.glsl", false };
}

ShaderManager::~ShaderManager()
{
	for (int i = 0; i < count; i++) {
		delete shaderPrograms[i].shaderProgram;
	}
	delete[] shaderPrograms;
}

ShaderProgram* ShaderManager::getShaderProgram(ShaderProgramType type)
{
	ShaderProgramSource& source = shaderPrograms[type];
	if (source.shaderProgram == nullptr) {
		source.shaderProgram = new ShaderProgram(source.usesLights);
		source.shaderProgram->loadFromFiles(source.vertexFilename, source.fragmentFilename);
	}
	return source.shaderProgram;
}



