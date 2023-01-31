#pragma once
#include <vector>
#include "InputListener.h"
#include "InputEvent.h"
#include "InputState.h"
#include "Input.h"

class InputHandler {

public:
	void handle(InputEvent e);
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);
private:
	std::vector<InputListener*> listeners;
};
