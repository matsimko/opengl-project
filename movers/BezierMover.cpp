#include "BezierMover.h"
#include <cmath>

int BezierMover::factorial(int n)
{
	if (n <= 1) {
		return 1;
	}
	return n * factorial(n - 1);
}

int BezierMover::numberOfCombinations(int n, int k)
{
	return (factorial(n)) / (factorial(n - k) * factorial(k));
}

float BezierMover::bernsteinPolynom(int i)
{
	return (float) numberOfCombinations(n, i) * std::pow(tParam, i) * std::pow((1 - tParam), n - i);
}

BezierMover::BezierMover(std::vector<glm::vec3> points, RenderableModel* obj, float tParamPerSec)
{
	this->points = points;
	this->obj = obj;
	this->tParamPerSec = tParamPerSec;

	this->forward = true;
	this->tParam = 0;
	this->n = points.size() - 1;

	obj->resetTranslation();
	obj->translate(points[0]);
}

void BezierMover::update(double dt)
{
	float tParamIncrement = dt * tParamPerSec;
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
	glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
	for (int i = 0; i < points.size(); i++) {
		position += points[i] * bernsteinPolynom(i);
	}
	obj->translateLast(position);
}
