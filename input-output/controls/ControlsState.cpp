#include "ControlsState.h"
#include "Controls.h"

void ControlsState::addCommand(Command* command)
{
	commands.push_back(command);
}

ControlsState::ControlsState(Controls* controls)
{
	this->controls = controls;
}

void ControlsState::handle(InputEvent e)
{
	for (auto cmd : commands) {
		if (cmd->executeIfTriggered(e)) {
			return;
		}
	}
}

void ControlsState::onControlsLeft()
{
	for (auto cmd : commands) {
		cmd->onControlsLeft();
	}
}

void ControlsState::onControlsEntered()
{
	for (auto cmd : commands) {
		cmd->onControlsEntered();
	}
}
