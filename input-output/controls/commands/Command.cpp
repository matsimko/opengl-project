#include "Command.h"
#include "HoldActionActivation.h"
#include "App.h"

void Command::execute(Action action)
{
	switch (action) {
	case Action::START:
		onActionStart();
		break;
	case Action::END:
		onActionEnd();
		break;
	case Action::NONE:
		//do nothing
		break;
	}
}

Command::Command(std::vector<Input*> inputs, ActionActivation* actionActivation)
{
	this->inputs = inputs;
	this->actionActivation = actionActivation;
}

bool Command::executeIfTriggered(InputEvent e)
{
	for (Input* input : inputs) {
		if (input->isTriggered(e)) {
			Action action = actionActivation->process(e.state);
			execute(action);
			return true;
		}
	}
	return false;
}

Command::~Command()
{
	for (Input* input : inputs) {
		delete input;
	}
	delete actionActivation;
}

void Command::onControlsLeft()
{
	Action action = actionActivation->onControlsLeft();
	execute(action);
}

void Command::onControlsEntered()
{
	Action action = Action::NONE;
	for (Input* input : inputs) {
		InputState inputState = App::getInstance().getWindow()->getStateOfInput(input);
		action = actionActivation->onControlsEntered(inputState);
		if (action != Action::NONE) {
			break;
		}
	}
	execute(action);
}

