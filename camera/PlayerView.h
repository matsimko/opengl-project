#pragma once
#include "CursorListener.h"
#include "Camera.h"
#include "Updatable.h"
#include "MovementVector.h"
#include "Renderable.h"
#include "Window.h"

class PlayerView : public CursorListener, public Updatable {
private:
	Camera* camera;
	Window *window;

	float movementSpeed;
	MovementVector vel; //velocity
	//normalized velocity across all directions (if I wanted to omit "up", I could add "normalizeForwardRight" method in MovementVector)
	MovementVector normalizedVel; 

	float verticalSensitivity;
	float horizontalSensitivity;
	bool invertedVerticalAxis;

	void updateNormalizedVel();

public:
	PlayerView(Camera* camera, float movementSpeed,
		float horizontalSensitivity, float verticalSensitivity, bool invertedVerticalAxis = false);

	virtual void update(double dt) override;

	// Inherited via CursorListener
	virtual void onCursorMoved(CursorEvent e) override;

	// +1 for forward, -1 for backward
	void addForwardVel(int value);
	// +1 for right, -1 for left
	void addRightVel(int value);
	// +1 for up, -1 for down
	void addUpVel(int value);

	Camera* getCamera();

	float getMovementSpeed();
	void setMovementSpeed(float value);
};
