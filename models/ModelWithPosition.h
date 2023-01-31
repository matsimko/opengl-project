#pragma once
#include "FlexibleModel.h"

class ModelWithPosition: public FlexibleModel {
public:
	ModelWithPosition(const float* vertices, int verticesCount, GLuint mode = GL_TRIANGLES);
	//Skybox uses this one (vertices have just the position without uv, but there is a texture map)
	ModelWithPosition(const float* vertices, int verticesCount, Texture *texture, GLuint mode = GL_TRIANGLES);
	ModelWithPosition(const float* vertices, int verticesCount, Material * material, GLuint mode = GL_TRIANGLES);
};
