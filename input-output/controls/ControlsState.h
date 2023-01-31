#pragma once
#include <vector>
#include "Command.h"
#include "InputEvent.h"

class Controls;

class ControlsState {
private:
	std::vector<Command*> commands;
protected:
	Controls* controls; //the "context" according to the State pattern
	void addCommand(Command* command);
public:
	ControlsState(Controls* controls);

	virtual void handle(InputEvent e);

	void onControlsLeft();
	void onControlsEntered();
};
