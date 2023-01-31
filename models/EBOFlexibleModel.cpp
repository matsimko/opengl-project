#include "EBOFlexibleModel.h"

void EBOFlexibleModel::init(std::vector<GLuint> indices)
{
	this->indices = indices;
}

void EBOFlexibleModel::doLoad(GLuint VBO)
{
	VectorFlexibleModel::doLoad(VBO);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
}

void EBOFlexibleModel::doDraw(ShaderProgram* shaderProgram)
{
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

EBOFlexibleModel::EBOFlexibleModel(std::vector<GLfloat> vertices, std::vector<GLuint> indices, std::vector<int> attrFloatCounts, GLuint mode)
	: VectorFlexibleModel(vertices, attrFloatCounts, mode)
{
	init(indices);
}

EBOFlexibleModel::EBOFlexibleModel(std::vector<GLfloat> vertices, std::vector<GLuint> indices, std::vector<int> attrFloatCounts, Texture* texture, GLuint mode)
	: VectorFlexibleModel(vertices, attrFloatCounts, texture, mode)
{
	init(indices);
}

EBOFlexibleModel::EBOFlexibleModel(std::vector<GLfloat> vertices, std::vector<GLuint> indices, std::vector<int> attrFloatCounts, Material* material, GLuint mode)
	: VectorFlexibleModel(vertices, attrFloatCounts, material, mode)
{
	init(indices);
}

EBOFlexibleModel::~EBOFlexibleModel()
{
}
