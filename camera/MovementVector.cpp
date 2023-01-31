#include "MovementVector.h"
#include "glm/vec3.hpp"
#include <glm/gtc/matrix_transform.hpp>

MovementVector::MovementVector()
{
	MovementVector(0, 0, 0);
}

MovementVector::MovementVector(float forward, float right, float up)
{
	this->forward = forward;
	this->right = right;
	this->up = up;
}

MovementVector MovementVector::normalize()
{
	glm::vec3 vec(forward, right, up);
	vec = glm::normalize(vec);
	return MovementVector(vec.x, vec.y, vec.z);
}

MovementVector MovementVector::multiply(float scalar)
{
	return MovementVector(forward * scalar, right * scalar, up * scalar);
}

bool MovementVector::isZeroVector()
{
	return forward == 0.f && right == 0.f && up == 0.f;
}

float MovementVector::getForward()
{
	return forward;
}

float MovementVector::getRight()
{
	return right;
}

float MovementVector::getUp()
{
	return up;
}

void MovementVector::addForward(float value)
{
	forward += value;
}

void MovementVector::addRight(float value)
{
	right += value;
}

void MovementVector::addUp(float value)
{
	up += value;
}
