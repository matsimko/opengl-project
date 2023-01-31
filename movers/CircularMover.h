#pragma once
#include "Updatable.h"
#include <glm/vec3.hpp>
#include "Transformable.h"

class CircularMover : public Updatable {
private:
	glm::vec3 centerPos;
	glm::vec3 startPos;
	float angularVelocity;
	glm::vec3 normal;
	float radius;

	Transformable* obj; //usually RenderableModel...

public:
	CircularMover(glm::vec3 centerPos, glm::vec3 startPos, Transformable* obj, float velocity = 10.f, glm::vec3 normal = glm::vec3(0,1,0));
	// Inherited via Updatable
	virtual void update(double dt) override;

};