#include "PlayerView.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ModelWithPositionNormal.h"
#include "tree.h"
#include "RenderableModel.h"
#include "App.h"
#include <glm/vec3.hpp>
#include <glm/ext/matrix_projection.hpp>

void PlayerView::updateNormalizedVel()
{
	if (vel.isZeroVector()) { //zero vectors have a zero length, so you would have to divide by zero
		normalizedVel = vel;
	}
	else {
		normalizedVel = vel.normalize();
	}
}

PlayerView::PlayerView(Camera* camera, float movementSpeed,
	float horizontalSensitivity, float verticalSensitivity, bool invertedVerticalAxis)
{
	this->camera = camera;
	this->window = App::getInstance().getWindow();
	this->movementSpeed = movementSpeed;
	this->horizontalSensitivity = horizontalSensitivity;
	this->verticalSensitivity = verticalSensitivity;
	this->invertedVerticalAxis = invertedVerticalAxis;

	//register itself to events that this PlayerView reacts to
	window->addCursorListener(this);
}


void PlayerView::onCursorMoved(CursorEvent e)
{
	//printf("cursor: %f %f\n", e.x, e.y);
	//if cursor is captured, rotate based on cursor's new position
	if (window->isCursorCaptured()) {
		double distX = e.x - e.prevX;
		double distY = e.y - e.prevY;
		double angleX = distX * horizontalSensitivity;
		double angleY = distY * verticalSensitivity;
		//the angle is in inverted axis by "default" (why?)
		if (!invertedVerticalAxis) {
			angleY = -angleY;
		}

		camera->rotateHorizontally(angleX);
		camera->rotateVertically(angleY);
	}
	
}

void PlayerView::addForwardVel(int value)
{
	vel.addForward(value);
	updateNormalizedVel();
}

void PlayerView::addRightVel(int value)
{
	vel.addRight(value);
	updateNormalizedVel();
}

void PlayerView::addUpVel(int value)
{
	vel.addUp(value);
	updateNormalizedVel();
}

Camera* PlayerView::getCamera()
{
	return camera;
}

float PlayerView::getMovementSpeed()
{
	return movementSpeed;
}

void PlayerView::setMovementSpeed(float value)
{
	this->movementSpeed = value;
}

void PlayerView::update(double dt)
{
	//update if not stationary
	if (!normalizedVel.isZeroVector()) {
		//distance = velocity * time
		MovementVector dist = normalizedVel.multiply(dt * movementSpeed);
		camera->translate(dist);
	}
}


