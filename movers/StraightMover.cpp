#include "StraightMover.h"
#include "glm/geometric.hpp"

StraightMover::StraightMover(glm::vec3 startPos, glm::vec3 endPos, Transformable* obj, float velocity)
{
	this->startPos = startPos;
	this->endPos = endPos;
	this->obj = obj;
	this->velocity = velocity;

	this->fullDist = glm::distance(startPos, endPos);
	this->dirVec = endPos - startPos;
	this->tParam = 0;
	this->forward = true;

	this->obj->resetTranslation();
	this->obj->translateLast(startPos);
}

void StraightMover::update(double dt)
{
	if (fullDist > 0) { //do nothing if endPos = startPos
		float dist = dt * velocity;
		float tParamIncrement = dist / fullDist;
		if (forward) {
			tParam += tParamIncrement;
			if (tParam >= 1) {
				tParam = 1 - (tParam - 1); //the extra distance is added to the way back
				forward = false;
			}
		}
		else {
			tParam -= tParamIncrement;
			if (tParam <= 0) {
				tParam = -tParam; //the extra distance is added to the way forward
				forward = true;
			}
		}

		obj->resetTranslation();
		obj->translateLast(startPos + tParam * dirVec); // X = A + ut
	}

}
