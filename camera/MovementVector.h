#pragma once

class MovementVector {
private:
	float forward; //forward/backward direction
	float right; //right/left direction
	float up; //up/down direction

public:
	MovementVector();
	MovementVector(float forward, float right, float up);

	MovementVector normalize();
	MovementVector multiply(float scalar);
	bool isZeroVector();

	float getForward();
	float getRight();
	float getUp();

	//the only mutating methods (they could just return a new vector but that might not be ideal performance-wise)
	void addForward(float value);
	void addRight(float value);
	void addUp(float value);

};