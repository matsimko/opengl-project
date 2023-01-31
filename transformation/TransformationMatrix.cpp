#include "TransformationMatrix.h"
#include <glm/gtc/matrix_transform.hpp>

TransformationMatrix::TransformationMatrix() : matrix(1.f)
{
}

void TransformationMatrix::translate(float x, float y, float z)
{
	glm::vec3 scaleVec(x, y, z);
	matrix = glm::translate(matrix, scaleVec);
}

void TransformationMatrix::scale(float x, float y, float z)
{
	glm::vec3 scaleVec(x, y, z);
	matrix = glm::scale(matrix, scaleVec);
}

void TransformationMatrix::rotate(float angle, float x, float y, float z)
{
	glm::vec3 axis(x, y, z);
	matrix = glm::rotate(matrix, angle, axis);
}

void TransformationMatrix::rotateDegrees(float angle, float x, float y, float z)
{
	this->rotate(glm::radians(angle), x, y, z);
}


void TransformationMatrix::setToIdentity()
{
	matrix = glm::mat4(1.0f);
}

GLfloat* TransformationMatrix::getDataAddress()
{
	return &matrix[0][0];
}

void TransformationMatrix::resetTranslation()
{
	matrix = glm::mat4(glm::mat3(matrix));
}

void TransformationMatrix::translate(glm::vec3 vec)
{
	matrix = glm::translate(matrix, vec);
}

void TransformationMatrix::scale(glm::vec3 vec)
{
	matrix = glm::scale(matrix, vec);
}

void TransformationMatrix::rotate(float angle, glm::vec3 axis)
{
	matrix = glm::rotate(matrix, angle, axis);
}

void TransformationMatrix::rotateDegrees(float angle, glm::vec3 axis)
{
	this->rotate(glm::radians(angle), axis);
}

void TransformationMatrix::translateLast(glm::vec3 vec)
{
	glm::mat4 transformationMat = glm::translate(glm::mat4(1.f), vec);
	matrix = transformationMat * matrix;
}


void TransformationMatrix::scaleLast(glm::vec3 vec)
{
	glm::mat4 transformationMat = glm::scale(glm::mat4(1.f), vec);
	matrix = transformationMat * matrix;
}

void TransformationMatrix::rotateLast(float angle, glm::vec3 axis)

{
	glm::mat4 transformationMat = glm::rotate(glm::mat4(1.f), angle, axis);
	matrix = transformationMat * matrix; 
}

void TransformationMatrix::rotateDegreesLast(float angle, glm::vec3 axis)
{
	this->rotateLast(glm::radians(angle), axis);
}

void TransformationMatrix::translateLast(float x, float y, float z)
{
	this->translateLast(glm::vec3(x, y, z));
}

void TransformationMatrix::scaleLast(float x, float y, float z)
{
	this->scaleLast(glm::vec3(x, y, z));
}

void TransformationMatrix::rotateLast(float angle, float x, float y, float z)
{
	this->rotateLast(angle, glm::vec3(x, y, z));
}

void TransformationMatrix::rotateDegreesLast(float angle, float x, float y, float z)
{
	this->rotateLast(angle, x, y, z);
}







glm::vec3 TransformationMatrix::applyTo(glm::vec3 vec)
{
	return glm::vec3(applyTo(glm::vec4(vec, 1.0f)));
}

glm::vec4 TransformationMatrix::applyTo(glm::vec4 vec)
{
	return matrix * vec;
}
