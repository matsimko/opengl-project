#pragma once
#include "Model.h"
#include "IdentifiableObject.h"
#include "ShaderProgram.h"

class Terrain : public IdentifiableObject {
private:
	int leftX;
	int topZ;
	int rows;
	int cols;
	float tileSize;

	Model* model;
	ShaderProgram* shaderProgram;

public:
	Terrain(int leftX, int topZ, int rows, int cols, float tileSize, Model* model, ShaderProgram* shaderProgram);

	// Inherited via IdentifiableObject
	virtual void render() override;

};
