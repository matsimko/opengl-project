#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::vec3
#include "Transformable.h"

class TransformationMatrix : public Transformable {
private:
	glm::mat4 matrix;

public:
	TransformationMatrix();
	void translate(float x, float y, float z) override;
	void scale(float x, float y, float z) override;
	void rotate(float angle, float x, float y, float z) override;
	void rotateDegrees(float angle, float x, float y, float z) override;
	void setToIdentity() override;

	void translate(glm::vec3 vec);
	void scale(glm::vec3 vec);
	void rotate(float angle, glm::vec3 axis);
	void rotateDegrees(float angle, glm::vec3 axis);

	// The following methods will make the new transformation matrix be applied last:
	// newM * M1 * M2 * M3 * vec
	void translateLast(glm::vec3 vec);
	void scaleLast(glm::vec3 vec);
	void rotateLast(float angle, glm::vec3 axis);
	void rotateDegreesLast(float angle, glm::vec3 axis);

	void translateLast(float x, float y, float z) override;
	void scaleLast(float x, float y, float z) override;
	void rotateLast(float angle, float x, float y, float z) override;
	void rotateDegreesLast(float angle, float x, float y, float z) override;

	glm::vec3 applyTo(glm::vec3 vec);
	glm::vec4 applyTo(glm::vec4 vec);

	GLfloat* getDataAddress();

	virtual void resetTranslation() override;
	//void setMatrix(glm::mat4 modelMatrix);
	//glm::mat4 getMatrix();
};