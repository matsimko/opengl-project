#include "Material.h"

void Material::initDefault()
{
	this->diffuseMap = nullptr;
	this->normalMap = nullptr;

	this->ambient = glm::vec4(1.f, 1.f, 1.f, 1.f);
	this->diffuse = glm::vec4(1.f, 1.f, 1.f, 1.f);
	this->specular = glm::vec4(1.f, 1.f, 1.f, 1.f);
	this->shininess = 32;
}

Material::Material()
{
	initDefault();
}

Material::Material(Texture* texture)
{
	initDefault();
	this->diffuseMap = texture;
}

Material::Material(Texture* texture, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float shininess)
{
	initDefault();
	this->diffuseMap = texture;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}

Material::Material(Texture* diffuseMap, Texture* normalMap)
{
	initDefault();
	this->diffuseMap = diffuseMap;
	this->normalMap = normalMap;
}

void Material::prep(ShaderProgram* shaderProgram)
{
	if (diffuseMap != nullptr) {
		shaderProgram->setUniformVariable("material.usesDiffuseMap", true);
		diffuseMap->prep(shaderProgram);
	}
	else {
		shaderProgram->setUniformVariable("material.usesDiffuseMap", false);
	}

	if (normalMap != nullptr) {
		shaderProgram->setUniformVariable("material.usesNormalMap", true);
		normalMap->prep(shaderProgram);
	}
	else {
		shaderProgram->setUniformVariable("material.usesNormalMap", false);
	}

	shaderProgram->setUniformVariable("material.ambient", ambient);
	shaderProgram->setUniformVariable("material.diffuse", diffuse);
	shaderProgram->setUniformVariable("material.specular", specular);
	shaderProgram->setUniformVariable("material.shininess", shininess);

}

void Material::setDiffuse(glm::vec4 diffuse)
{
	this->diffuse = diffuse;
}
