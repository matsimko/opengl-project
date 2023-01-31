#pragma once
#include "FlexibleModel.h"

class ModelWithPositionNormal : public FlexibleModel {
private:

public:
	ModelWithPositionNormal(const float* vertices, int verticesCount, GLuint mode = GL_TRIANGLES);
};
