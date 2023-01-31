#pragma once
#include "Texture.h"
#include "glm/vec4.hpp"
#include "ShaderProgram.h"

class Material {
private:
	Texture* diffuseMap;
	Texture* normalMap;
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	float shininess; //0-1000 usually

	void initDefault();
public:
	Material();
	Material(Texture* texture);
	Material(Texture* texture, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float shininess);
	Material(Texture* diffuseMap, Texture* normalMap);
	void prep(ShaderProgram* shaderProgram);

	void setDiffuse(glm::vec4 diffuse);
};
