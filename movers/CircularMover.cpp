#include "CircularMover.h"
#include "glm/geometric.hpp"

CircularMover::CircularMover(glm::vec3 centerPos, glm::vec3 startPos, Transformable* obj, float velocity, glm::vec3 normal)
{
	this->centerPos = centerPos;
	this->startPos = startPos;
	this->obj = obj;
	this->radius = glm::distance(centerPos, startPos);
	if (radius > 0) {
		this->angularVelocity = velocity / radius; //make the speed the same for all radiuses
	}
	this->normal = normal;

	obj->resetTranslation();
	obj->translateLast(startPos);
}

void CircularMover::update(double dt)
{
	if (radius > 0) {
		obj->translateLast(-centerPos);
		obj->rotateLast(angularVelocity * dt, normal);
		obj->translateLast(centerPos);
	}
	
}
