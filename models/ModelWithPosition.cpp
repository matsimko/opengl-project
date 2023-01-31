#include "ModelWithPosition.h"

ModelWithPosition::ModelWithPosition(const float* vertices, int verticesCount, GLuint mode)
	: FlexibleModel(vertices, verticesCount, {3}, mode)
{

}

ModelWithPosition::ModelWithPosition(const float* vertices, int verticesCount, Texture* texture, GLuint mode)
	: FlexibleModel(vertices, verticesCount, { 3 }, texture, mode)
{
}

ModelWithPosition::ModelWithPosition(const float* vertices, int verticesCount, Material* material, GLuint mode)
	: FlexibleModel(vertices, verticesCount, { 3 }, material, mode)
{
}

