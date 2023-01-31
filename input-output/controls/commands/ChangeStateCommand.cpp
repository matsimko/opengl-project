#include "ChangeStateCommand.h"
#include "App.h"

ChangeStateCommand::ChangeStateCommand(std::vector<Input*> inputs, ActionActivation* actionActivation,
	ControlsState* state)
	:Command(inputs, actionActivation)
{
	this->state = state;
}

void ChangeStateCommand::onActionStart()
{
	App::getInstance().getScene()->getControls()->setState(state);
}

void ChangeStateCommand::onActionEnd()
{
}
