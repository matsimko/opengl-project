#pragma once
#include "Updatable.h"
#include <glm/vec3.hpp>
#include "Transformable.h"

class StraightMover : public Updatable {
private:
	glm::vec3 startPos;
	glm::vec3 endPos;
	float velocity;
	float tParam;
	float fullDist;
	bool forward;
	glm::vec3 dirVec;

	Transformable* obj; //usually RenderableModel...

public:
	StraightMover(glm::vec3 startPos, glm::vec3 endPos, Transformable* obj, float velocity = 10.f);
	// Inherited via Updatable
	virtual void update(double dt) override;

};