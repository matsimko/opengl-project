#pragma once
#include "IdentifiableObject.h"
#include "Loadable.h" 
#include "ShaderProgram.h"
#include "Model.h"
#include "TransformationMatrix.h"
#include "Updatable.h"

class RenderableModel : public IdentifiableObject, public Transformable, public Updatable {
private:
	Model* model;
	ShaderProgram* shaderProgram;
	TransformationMatrix modelMatrix;
	Updatable* updatable;
public:
	RenderableModel(Model* model, ShaderProgram* shaderProgram, bool uniqueId = false);
	// Inherited via Renderable
	virtual void render() override;
	// Inherited via Transformable
	virtual void translate(float x, float y, float z) override;
	virtual void scale(float x, float y, float z) override;
	virtual void rotate(float angle, float x, float y, float z) override;
	virtual void rotateDegrees(float angle, float x, float y, float z) override;
	virtual void setToIdentity() override;
	virtual void translateLast(float x, float y, float z) override;
	virtual void scaleLast(float x, float y, float z) override;
	virtual void rotateLast(float angle, float x, float y, float z) override;
	virtual void rotateDegreesLast(float angle, float x, float y, float z) override;

	virtual void translate(glm::vec3 vec) override;
	virtual void scale(glm::vec3 vec) override;
	virtual void rotate(float angle, glm::vec3 axis) override;
	virtual void rotateDegrees(float angle, glm::vec3 axis) override;
	virtual void translateLast(glm::vec3 vec) override;
	virtual void scaleLast(glm::vec3 vec) override;
	virtual void rotateLast(float angle, glm::vec3 axis) override;
	virtual void rotateDegreesLast(float angle, glm::vec3 axis) override;

	virtual void resetTranslation() override;

	Model* getModel();

	RenderableModel* clone();

	// Inherited via Updatable
	virtual void update(double dt) override;

	void setUpdatable(Updatable* updatable);
};
