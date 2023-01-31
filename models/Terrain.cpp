#include "Terrain.h"

Terrain::Terrain(int leftX, int topZ, int rows, int cols, float tileSize, Model* model, ShaderProgram* shaderProgram)
{
	this->leftX = leftX;
	this->topZ = topZ;
	this->rows = rows;
	this->cols = cols;
	this->tileSize = tileSize;
	this->model = model;
	this->shaderProgram = shaderProgram;
}

void Terrain::render()
{
	TransformationMatrix modelMatrix;

	shaderProgram->use();
	glStencilFunc(GL_ALWAYS, getId(), 0xFF);
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			modelMatrix = TransformationMatrix();
			modelMatrix.translate(leftX + tileSize * c, 0, topZ + tileSize * r);
			modelMatrix.scale(tileSize, 1.f, tileSize);
			shaderProgram->setUniformVariable("modelMatrix", modelMatrix);
			model->draw(shaderProgram);
		}
	}
	/*modelMatrix = TransformationMatrix();
	modelMatrix.scale(tileSize * rows, 1.f, tileSize * cols);
	shaderProgram->setUniformVariable("modelMatrix", modelMatrix);
	model->draw(shaderProgram);*/
}
