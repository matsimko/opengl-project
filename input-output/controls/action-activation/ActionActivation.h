#pragma once
#include "InputState.h"

enum class Action {
	START, END, NONE
};

//the base class for different activations of actions (hold, toggle or tap)
class ActionActivation {
protected:
	virtual Action onPress();
	virtual Action onRelease();

public:
	Action process(InputState inputState);
	
	virtual Action onControlsLeft();
	virtual Action onControlsEntered(InputState inputState);
	
};
