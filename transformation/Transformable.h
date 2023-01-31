#pragma once

class Transformable {
public:
	virtual void translate(float x, float y, float z) = 0;
	virtual void scale(float x, float y, float z) = 0;
	virtual void rotate(float angle, float x, float y, float z) = 0;
	virtual void rotateDegrees(float angle, float x, float y, float z) = 0;
	virtual void setToIdentity() = 0;

	virtual void translateLast(float x, float y, float z) = 0;
	virtual void scaleLast(float x, float y, float z) = 0;
	virtual void rotateLast(float angle, float x, float y, float z) = 0;
	virtual void rotateDegreesLast(float angle, float x, float y, float z) = 0;

	virtual void translate(glm::vec3 vec) = 0;
	virtual void scale(glm::vec3 vec) = 0;
	virtual void rotate(float angle, glm::vec3 axis) = 0;
	virtual void rotateDegrees(float angle, glm::vec3 axis) = 0;

	virtual void translateLast(glm::vec3 vec) = 0;
	virtual void scaleLast(glm::vec3 vec) = 0;
	virtual void rotateLast(float angle, glm::vec3 axis) = 0;
	virtual void rotateDegreesLast(float angle, glm::vec3 axis) = 0;

	virtual void resetTranslation() = 0;
};
