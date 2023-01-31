#include "Camera.h"
#include "CameraListener.h"
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

void Camera::updateProjectionMatrix()
{
	projectionMatrix = glm::perspective(fov, aspect, near, far);
	notifyProjectionMatrixChanged();
}

void Camera::updateViewMatrix()
{
	target.x = cos(glm::radians(horizontalAngle)) * cos(glm::radians(verticalAngle));
	target.y = sin(glm::radians(verticalAngle));
	target.z = sin(glm::radians(horizontalAngle)) * cos(glm::radians(verticalAngle));

	//printf("target: [%f, %f, %f]\n", target.x, target.y, target.z);
	viewMatrix = glm::lookAt(pos, pos + target, up);
	notifyViewMatrixChanged();
}

void Camera::notifyViewMatrixChanged()
{
	for (auto listener : listeners) {
		listener->onViewMatrixChanged(this);
	}
}

void Camera::notifyProjectionMatrixChanged()
{
	for (auto listener : listeners) {
		listener->onProjectionMatrixChanged(this);
	}
}

Camera::Camera(float aspect)
{
	this->near = 0.1f;
	this->far = 100.f;
	this->fov = 45.f;
	this->aspect = aspect;

	this->pos = glm::vec3(0.f, 0.f, 0.f);
	this->up = glm::vec3(0.f, 1.f, 0.f);
	this->horizontalAngle = 270.f; //negative x is to the left and negative z is forward on spawn
	this->verticalAngle = 0.f;

	updateProjectionMatrix();
	updateViewMatrix();
}

void Camera::addListener(CameraListener* listener)
{
	listeners.push_back(listener);
}

void Camera::onResize(Window* window)
{
	aspect = window->getAspectRatio();
	updateProjectionMatrix();
}

void Camera::translate(float forwardDist, float rightDist, float upDist)
{
	//getting the relative "right" and "up" is really possible only because vertical is (90,90), right?

	pos += forwardDist * target; //target is the front direction
	glm::vec3 right = glm::normalize(glm::cross(target, up));
	pos += rightDist * right;
	//the first option is to leave "up" always the same (the "earthly" option)
	pos += upDist * up;
	//the second option is to update "up" relative to target (=front) (the "space has no up" option)
	//pos += upDist * glm::normalize(glm::cross(right, target));


	updateViewMatrix();
}

void Camera::translate(MovementVector dist)
{
	translate(dist.getForward(), dist.getRight(), dist.getUp());
}

void Camera::rotateHorizontally(float angle)
{
	horizontalAngle = fmod(horizontalAngle + angle, 360);

	updateViewMatrix();
}

void Camera::rotateVertically(float angle)
{
	verticalAngle += angle;
	if (verticalAngle > 89.f) {
		verticalAngle = 89.f;
	}
	else if (verticalAngle < -89.f) {
		verticalAngle = -89.f;
	}

	updateViewMatrix();
}

glm::mat4& Camera::getProjectionMatrix()
{
	return projectionMatrix;
}

glm::mat4& Camera::getViewMatrix()
{
	return viewMatrix;
}

glm::vec3& Camera::getPos()
{
	return pos;
}

void Camera::notify()
{
	notifyProjectionMatrixChanged();
	notifyViewMatrixChanged();
}

glm::vec3 Camera::getTarget()
{
	return target;
}
