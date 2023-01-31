#include "ShaderProgram.h"

#include "Camera.h"

#include <stdio.h>
#include <stdexcept>

void ShaderProgram::compile()
{
	id = glCreateProgram();
	glAttachShader(id, fragmentShader.getId());
	glAttachShader(id, vertexShader.getId());
	glLinkProgram(id);

	GLint status;
	glGetProgramiv(id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(id, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		exit(1);
	}

	//use(); //the program seems to be automatically in use after creation
	viewMatrixId = getUniformLocation("viewMatrix");
	projectionMatrixId = getUniformLocation("projectionMatrix");
	camPosId = getUniformLocation("camPos");

}

ShaderProgram::ShaderProgram(bool usesLights)
	: vertexShader(GL_VERTEX_SHADER), fragmentShader(GL_FRAGMENT_SHADER)
{
	this->usesLights = usesLights;
	id = viewMatrixId = projectionMatrixId = camPosId = 0;
}

void ShaderProgram::loadFromStrings(const char* vertexCode, const char* fragmentCode)
{
	vertexShader.loadFromString(vertexCode);
	fragmentShader.loadFromString(fragmentCode);

	compile();
}

void ShaderProgram::loadFromFiles(const char* vertexFilename, const char* fragmentFilename)
{
	vertexShader.loadFromFile(vertexFilename);
	fragmentShader.loadFromFile(fragmentFilename);

	compile();
}

void ShaderProgram::use()
{
	glUseProgram(id);
}

void ShaderProgram::onProjectionMatrixChanged(Camera* camera)
{
	use(); //the program needs to be used before setting uniform location can happen!!!
	setUniformVariable(projectionMatrixId, camera->getProjectionMatrix());
}

void ShaderProgram::onViewMatrixChanged(Camera* camera)
{
	use(); //the program needs to be used before setting uniform location can happen!!!
	setViewMatrix(camera->getViewMatrix());
	setCamPos(camera->getPos());
}

void ShaderProgram::setViewMatrix(glm::mat4 viewMatrix)
{
	setUniformVariable(viewMatrixId, viewMatrix);
}

void ShaderProgram::setCamPos(glm::vec3 camPos)
{
	if (camPosId != -1) {
		setUniformVariable(camPosId, camPos);
	}
}

bool ShaderProgram::isUsingLights()
{
	return usesLights;
}

/*void ShaderProgram::onLightPositionChanged(Light* light)
{
	use();
	setUniformVariable(light->getPosUniformName(), light->getPos());
}*/

GLint ShaderProgram::getUniformLocation(const char* name)
{
	if (uniformsMap.find(name) == uniformsMap.end()) {
		GLint uniformId = glGetUniformLocation(this->id, name);
		if (uniformId == -1) {
			printf("\"%s\" does not correspond to an active uniform variable in the program.\n", name);
		}
		
		uniformsMap.insert({ name, uniformId });
		return uniformId;
	}

	return uniformsMap.at(name);
	
	
}

void ShaderProgram::setUniformVariable(const char* name, glm::mat4& matrix)
{
	GLint varId = getUniformLocation(name);
	setUniformVariable(varId, matrix);
}

void ShaderProgram::setUniformVariable(const char* name, TransformationMatrix& matrix)
{
	GLint varId = getUniformLocation(name);
	setUniformVariable(varId, matrix);
}

void ShaderProgram::setUniformVariable(const char* name, glm::vec3& vec)
{
	GLint varId = getUniformLocation(name);
	setUniformVariable(varId, vec);
}

void ShaderProgram::setUniformVariable(const char* name, glm::vec4& vec)
{
	GLint varId = getUniformLocation(name);
	setUniformVariable(varId, vec);
}

void ShaderProgram::setUniformVariable(const char* name, int num)
{
	GLint varId = getUniformLocation(name);
	setUniformVariable(varId, num);
}

void ShaderProgram::setUniformVariable(const char* name, float num)
{
	GLint varId = getUniformLocation(name);
	setUniformVariable(varId, num);
}

void ShaderProgram::setUniformVariable(GLint varId, glm::mat4& matrix)
{
	if (varId != -1) {
		glUniformMatrix4fv(varId, 1, GL_FALSE, &matrix[0][0]);
	}
	
}

void ShaderProgram::setUniformVariable(GLint varId, TransformationMatrix& matrix)
{
	if (varId != -1) {
		glUniformMatrix4fv(varId, 1, GL_FALSE, matrix.getDataAddress());
	}
}

void ShaderProgram::setUniformVariable(GLint varId, glm::vec3& vec)
{
	if (varId != -1) {
		glUniform3fv(varId, 1, &vec[0]);
	}
}

void ShaderProgram::setUniformVariable(GLint varId, glm::vec4& vec)
{
	if (varId != -1) {
		glUniform4fv(varId, 1, &vec[0]);
	}
}

void ShaderProgram::setUniformVariable(GLint varId, float num)
{
	if (varId != -1) {
		glUniform1f(varId, num);
	}
}

void ShaderProgram::setUniformVariable(GLint varId, int num)
{
	if (varId != -1) {
		glUniform1i(varId, num);
	}
}

