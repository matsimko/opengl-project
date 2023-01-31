#pragma once
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp>
#include <vector>
#include "ShaderProgram.h"
#include "WindowListener.h"
#include "Window.h"
#include "MovementVector.h"

class CameraListener;

class Camera : public WindowListener {

private:
	glm::mat4 projectionMatrix;
	float fov; //field of view
	//Vertices in range <near, far> relative to the camera will be shown on the screen, the rest will be clipped.
	float near;
	float far;
	float aspect; //aspect "ratio" (e.g. aspect ratio = 4:3 -> aspect = 1.33)

	glm::mat4 viewMatrix;
	glm::vec3 pos; //position (=eye) of the camera
	glm::vec3 target; //direction relative to the pos
	glm::vec3 up; //which direction is up
	//angles in degrees that determine the target vec
	float horizontalAngle; // <0,360)
	float verticalAngle; //  <89, 89> (anything up to (-90, 90) is fine)

	void updateProjectionMatrix();
	void updateViewMatrix();


	std::vector<CameraListener*> listeners;
	void notifyViewMatrixChanged();
	void notifyProjectionMatrixChanged();
public:
	Camera(float aspect);
	void addListener(CameraListener* listener);
	//void removeListener(CameraListener* listener);

	// Inherited via WindowListener
	virtual void onResize(Window* window) override;

	void translate(float forwardDist, float rightDist, float upDist = 0.f);
	void translate(MovementVector dist);
	void rotateHorizontally(float angle);
	void rotateVertically(float angle);


	glm::mat4& getProjectionMatrix();
	glm::mat4& getViewMatrix();
	glm::vec3& getPos();
	//call this to let listeners get the initial camera state
	void notify();

	glm::vec3 getTarget();

};
