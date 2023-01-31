#pragma once
#include "ShaderProgram.h"
#include "ModelWithPosition.h"
#include "CubeMapFilenames.h"
#include "Texture.h"
#include "Background.h"

class Skybox : public Background {
private:
	Model* model;
	ShaderProgram* shaderProgram;


public:
	Skybox(const float * vertices, int verticesCount, CubeMapFilenames cubeMapFilenames);

	// Inherited via Background (CameraListener)
	virtual void onViewMatrixChanged(Camera* camera) override;
	virtual void onProjectionMatrixChanged(Camera* camera) override;


	// Inherited via Background (Renderable)
	virtual void render() override;

};
