#include "AdvancedModel.h"


void AdvancedModel::doLoad(GLuint VBO)
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//offsetoff is macro for the offset in bytes of a struct variable from the start of the struct (in C++ struct always has a sequential layout)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(AdvancedVertex), (void*)offsetof(AdvancedVertex, pos));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(AdvancedVertex), (void*)offsetof(AdvancedVertex, normal));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(AdvancedVertex), (void*)offsetof(AdvancedVertex, uv));

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
}


AdvancedModel::AdvancedModel(std::vector<AdvancedVertex> vertices, std::vector<GLuint> indices, Material* material)
	: Model(material)
{
	this->vertices = vertices;
	this->indices = indices;
}

void AdvancedModel::doDraw(ShaderProgram* shaderProgram)
{
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
