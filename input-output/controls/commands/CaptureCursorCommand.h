#pragma once
#include "Command.h"
#include "App.h"

class CaptureCursorCommand : public Command {
private:
	//I store app instead of window so that if, in a paralel universe, I had multiple windows, I would use the current one this way
	App& app;
protected:
	// Inherited via Command
	virtual void onActionStart() override;
	virtual void onActionEnd() override;

public:
	CaptureCursorCommand(std::vector<Input*> inputs, ActionActivation* actionActivation);
};
