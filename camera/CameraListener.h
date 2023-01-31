#pragma once

class Camera;

//If the program was multithreaded and the camera could be changed while the listeners were reacting to a previous change, 
//then it would be required to send the changed matrices in the listener methods (because the old matrices might have been already updated)
class CameraListener {
public:
	virtual void onViewMatrixChanged(Camera* camera) = 0;
	virtual void onProjectionMatrixChanged(Camera* camera) = 0;

};
