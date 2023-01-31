#include "RenderableModel.h"

void RenderableModel::translate(float x, float y, float z)
{
	modelMatrix.translate(x, y, z);
}

void RenderableModel::scale(float x, float y, float z)
{
	modelMatrix.scale(x, y, z);
}

void RenderableModel::rotate(float angle, float x, float y, float z)
{
	modelMatrix.rotate(angle, x, y, z);
}

void RenderableModel::rotateDegrees(float angle, float x, float y, float z)
{
	modelMatrix.rotateDegrees(angle, x, y, z);
}

void RenderableModel::setToIdentity()
{
	modelMatrix.setToIdentity();
}

Model* RenderableModel::getModel()
{
	return model;
}

RenderableModel* RenderableModel::clone()
{
	RenderableModel* cloned = new RenderableModel(model, shaderProgram, hasUniqueId());
	cloned->modelMatrix = modelMatrix; //the matrix is stored by value so this is fine
	return cloned;
}

void RenderableModel::update(double dt)
{
	if (updatable != nullptr) {
		updatable->update(dt);
	}
}

void RenderableModel::setUpdatable(Updatable* updatable)
{
	this->updatable = updatable;
}

void RenderableModel::translate(glm::vec3 vec)
{
	modelMatrix.translate(vec);
}

void RenderableModel::scale(glm::vec3 vec)
{
	modelMatrix.scale(vec);
}

void RenderableModel::rotate(float angle, glm::vec3 axis)
{
	modelMatrix.rotate(angle, axis);
}

void RenderableModel::rotateDegrees(float angle, glm::vec3 axis)
{
	modelMatrix.rotateDegrees(angle, axis);
}

void RenderableModel::translateLast(glm::vec3 vec)
{
	modelMatrix.translateLast(vec);
}

void RenderableModel::scaleLast(glm::vec3 vec)
{
	modelMatrix.scaleLast(vec);
}

void RenderableModel::rotateLast(float angle, glm::vec3 axis)
{
	modelMatrix.rotateLast(angle, axis);
}

void RenderableModel::rotateDegreesLast(float angle, glm::vec3 axis)
{
	modelMatrix.rotateDegreesLast(angle, axis);
}

void RenderableModel::resetTranslation()
{
	modelMatrix.resetTranslation();
}

void RenderableModel::translateLast(float x, float y, float z)
{
	modelMatrix.translateLast(x, y, z);
}

void RenderableModel::scaleLast(float x, float y, float z)
{
	modelMatrix.scaleLast(x, y, z);
}

void RenderableModel::rotateLast(float angle, float x, float y, float z)
{
	modelMatrix.rotateLast(angle, x, y, z);
}

void RenderableModel::rotateDegreesLast(float angle, float x, float y, float z)
{
	modelMatrix.rotateDegreesLast(angle, x, y, z);
}

RenderableModel::RenderableModel(Model* model, ShaderProgram* shaderProgram, bool uniqueId)
	: IdentifiableObject(uniqueId)
{
	this->model = model;
	this->shaderProgram = shaderProgram;
	this->updatable = nullptr;
}

void RenderableModel::render()
{
	shaderProgram->use();
 	shaderProgram->setUniformVariable("modelMatrix", modelMatrix);
	glStencilFunc(GL_ALWAYS, getId(), 0xFF);
	model->draw(shaderProgram);
}
