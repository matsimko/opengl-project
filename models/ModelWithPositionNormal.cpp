#include "ModelWithPositionNormal.h"

ModelWithPositionNormal::ModelWithPositionNormal(const float* vertices, int verticesCount, GLuint mode)
	: FlexibleModel(vertices, verticesCount, {3, 3}, mode)
{
}
