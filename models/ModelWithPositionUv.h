#pragma once
#include "FlexibleModel.h"

class ModelWithPositionUv : public FlexibleModel {
private:

public:
	ModelWithPositionUv(const float* vertices, int verticesCount, Texture* texture, GLuint mode = GL_TRIANGLES);
};
