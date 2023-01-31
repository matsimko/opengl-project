#include "FlexibleModel.h"


FlexibleModel::FlexibleModel(const float* vertices, int verticesCount, std::vector<int> attrFloatCounts, Texture* texture, GLuint mode)
	: Model(new Material(texture))
{
	init(vertices, verticesCount, attrFloatCounts, mode);
}

FlexibleModel::FlexibleModel(const float* vertices, int verticesCount, std::vector<int> attrFloatCounts, Material* material, GLuint mode)
	: Model(material)
{
	init(vertices, verticesCount, attrFloatCounts, mode);
}

FlexibleModel::FlexibleModel(const float* vertices, int verticesCount, std::vector<int> attrFloatCounts, GLuint mode)
	: Model()
{
	init(vertices, verticesCount, attrFloatCounts, mode);
}

void FlexibleModel::init(const float* vertices, int verticesCount, std::vector<int> attrFloatCounts, GLuint mode)
{
	this->vertices = new float[verticesCount];
	this->verticesCount = verticesCount;
	memcpy(this->vertices, vertices, sizeof(float) * verticesCount);
	this->mode = mode;
	this->attrFloatCounts = attrFloatCounts;
	this->vertexFloatCount = 0;
	for (int i = 0; i < attrFloatCounts.size(); i++) {
		vertexFloatCount += attrFloatCounts[i];
	}
}

FlexibleModel::~FlexibleModel()
{
	delete[] vertices;
}

void FlexibleModel::doLoad(GLuint VBO)
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesCount, vertices, GL_STATIC_DRAW);
	int attrOffset = 0;
	for (int i = 0; i < attrFloatCounts.size(); i++) {
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attrFloatCounts[i], GL_FLOAT, GL_FALSE,
			sizeof(float) * vertexFloatCount, (void*)(sizeof(float) * attrOffset));
		attrOffset += attrFloatCounts[i];
	}
}

void FlexibleModel::doDraw(ShaderProgram* shaderProgram)
{
	glDrawArrays(mode, 0, verticesCount / vertexFloatCount);
}


