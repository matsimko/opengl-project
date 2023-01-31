#pragma once
#include <vector>
#include "Input.h"
#include "InputEvent.h"
#include "ActionActivation.h"


//an action to be done when its assigned input is triggered
//this is a baseclass that takes care of finding out if the input was triggered and if yes then delegates the work to its descendants.

//Because Visual Studio apperently doesn't offer constructor generation,
//it would be more time efficient to use composition instead of inheritance (no need to pass inputs and action activation)
//and it would probably also make more sense conceptually to separate it.
class Command {
private:
	//list of inputs that can trigger the command (usually just one key)
	std::vector<Input*> inputs;
	//type of activation (hold, toggle, tap)
	ActionActivation* actionActivation;

	void execute(Action action);

protected:
	Command(std::vector<Input*> inputs, ActionActivation* actionActivation);
	virtual void onActionStart() = 0;
	virtual void onActionEnd() = 0;
public:
	/*Executes the command if one of its inputs has been triggered (template method).
	  Returns true iff the event was triggered.*/
	bool executeIfTriggered(InputEvent e);

	~Command();

	//the hold actions need to be cancelled before leaving the state (otherwise things could happen like a player keeping moving forward)
	void onControlsLeft();

	//called before the wanted controls are set,
    //so that HoldAction can check key state (e.g., if the user held some button when the switch happened, the hold action in the new controls would get activated)
	void onControlsEntered();
};
