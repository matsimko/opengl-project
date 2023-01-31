#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>  
#include "Shader.h"
#include <exception>
#include "CameraListener.h"
#include <glm/mat4x4.hpp>
#include "TransformationMatrix.h"
#include <map>
//#include "LightListener.h"

class ShaderProgram : public CameraListener /*, public LightListener*/ {
private:
	GLuint id;
	Shader vertexShader;
	Shader fragmentShader;
	void compile();

	GLint viewMatrixId;
	GLint projectionMatrixId;
	GLint camPosId;

	//cache previous setUniformVariable names in a map, which increases performance (and also prevents printf from spamming the console)
	std::map<const char*, GLint> uniformsMap;
	//get uniform location for variable of the given name
	GLint getUniformLocation(const char* name);

	void setUniformVariable(GLint varId, glm::mat4& matrix);
	void setUniformVariable(GLint varId, TransformationMatrix& matrix);
	void setUniformVariable(GLint varId, glm::vec3& vec);
	void setUniformVariable(GLint varId, glm::vec4& vec);
	void setUniformVariable(GLint varId, float num);
	void setUniformVariable(GLint varId, int num);

	bool usesLights;
public:
	ShaderProgram(bool usesLights);
	void loadFromStrings(const char* vertexCode, const char* fragmentCode);
	void loadFromFiles(const char* vertexFilename, const char* fragmentFilename);
	void use();
	
	void setUniformVariable(const char* name, glm::mat4& matrix);
	void setUniformVariable(const char* name, TransformationMatrix& matrix);
	void setUniformVariable(const char* name, glm::vec3& vec);
	void setUniformVariable(const char* name, glm::vec4& vec);
	void setUniformVariable(const char* name, int num);
	void setUniformVariable(const char* name, float num);


	void onProjectionMatrixChanged(Camera* camera) override;
	void onViewMatrixChanged(Camera* camera) override;
	void setViewMatrix(glm::mat4 viewMatrix);
	void setCamPos(glm::vec3 camPos);

	bool isUsingLights();


	// Inherited via LightListener
	//virtual void onLightPositionChanged(Light* light) override;

};
