#pragma once
#include "CursorListener.h"
#include "Command.h"
#include "PlayerView.h"
#include "InputListener.h"
#include "ControlsState.h"
#include "RenderableModel.h"

//Manage memory of Controls and ControlsState somehow properly!

//It would be simpler if I made these Controls to be ControlsState as well
//and instead had a Controls context class that wouldn't have its own commands
//(I have to implement stuff at two places this way...)
class Controls : public InputListener {
private:
	ControlsState* state;
	std::vector<Command*> commands;

public:
	Controls();

	// Inherited via KeyListener
	virtual void onInput(InputEvent e) override;

	void addCommand(Command * command);
	void setState(ControlsState* state);

	//giving this method to Controls, because it would take too much time to figure out a more general solution
	virtual RenderableModel* getItem();

};
