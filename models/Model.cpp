#include "Model.h"


Model::Model(Material* material)
{
	this->VAO = -1;
	this->material = material;
}

Model::~Model()
{
	delete material;
}

void Model::load()
{
	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO

	GLuint VBO;
	//vertex buffer object (VBO)
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	//let the descendants handle this
	doLoad(VBO);
}

void Model::draw(ShaderProgram* shaderProgram)
{
	glBindVertexArray(VAO);
	material->prep(shaderProgram);
	doDraw(shaderProgram);
}
