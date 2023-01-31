#include "VectorFlexibleModel.h"

#include "EBOFlexibleModel.h"

void VectorFlexibleModel::init(std::vector<GLfloat> vertices, std::vector<int> attrFloatCounts, GLuint mode)
{
	this->vertices = vertices;
	this->attrFloatCounts = attrFloatCounts;
	this->mode = mode;

	this->vertexFloatCount = 0;
	for (int i = 0; i < attrFloatCounts.size(); i++) {
		vertexFloatCount += attrFloatCounts[i];
	}
}

void VectorFlexibleModel::doLoad(GLuint VBO)
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	int attrOffset = 0;
	for (int i = 0; i < attrFloatCounts.size(); i++) {
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attrFloatCounts[i], GL_FLOAT, GL_FALSE,
			sizeof(float) * vertexFloatCount, (void*)(sizeof(float) * attrOffset));
		attrOffset += attrFloatCounts[i];
	}
}

void VectorFlexibleModel::doDraw(ShaderProgram* shaderProgram)
{
	glDrawArrays(mode, 0, verticesCount / vertexFloatCount);
}

VectorFlexibleModel::VectorFlexibleModel(std::vector<GLfloat> vertices, std::vector<int> attrFloatCounts, GLuint mode)
	: Model()
{
	init(vertices, attrFloatCounts, mode);
}

VectorFlexibleModel::VectorFlexibleModel(std::vector<GLfloat> vertices, std::vector<int> attrFloatCounts, Texture* texture, GLuint mode)
	: Model(new Material(texture))
{
	init(vertices, attrFloatCounts, mode);
}

VectorFlexibleModel::VectorFlexibleModel(std::vector<GLfloat> vertices, std::vector<int> attrFloatCounts, Material* material, GLuint mode)
	: Model(material)
{
	init(vertices, attrFloatCounts, mode);
}

VectorFlexibleModel::~VectorFlexibleModel()
{
}

