#include "ModelWithPositionUv.h"


ModelWithPositionUv::ModelWithPositionUv(const float* vertices, int verticesCount, Texture* texture, GLuint mode)
	: FlexibleModel(vertices, verticesCount, {3, texture->getNumberOfComponents()}, texture, mode)

{
}
