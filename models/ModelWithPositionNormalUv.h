#pragma once

#pragma once
#include "FlexibleModel.h"

class ModelWithPositionNormalUv : public FlexibleModel {
private:

public:
	ModelWithPositionNormalUv(const float* vertices, int verticesCount, Texture* texture, GLuint mode = GL_TRIANGLES);
};

