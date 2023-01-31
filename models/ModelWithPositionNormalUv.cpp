#include "ModelWithPositionNormalUv.h"

ModelWithPositionNormalUv::ModelWithPositionNormalUv(const float* vertices, int verticesCount, Texture* texture, GLuint mode)
	: FlexibleModel(vertices, verticesCount, {3, 3, texture->getNumberOfComponents()}, texture, mode)
{
}
