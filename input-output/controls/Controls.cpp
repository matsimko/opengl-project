#include "Controls.h"


Controls::Controls()
{
	state = nullptr;
}

void Controls::onInput(InputEvent e)
{
	if (state == nullptr) {
		for (auto cmd : commands) {
			if (cmd->executeIfTriggered(e)) {
				return;
			}
		}
	}
	else {
		state->handle(e);
	}
	
}


void Controls::addCommand(Command* command)
{
	commands.push_back(command);
}

void Controls::setState(ControlsState* state)
{
	if (this->state == nullptr) {
		for (auto cmd : commands) {
			cmd->onControlsLeft();
		}
	}
	else {
		this->state->onControlsLeft();
	}


	this->state = state;
	if (this->state == nullptr) {
		for (auto cmd : commands) {
			cmd->onControlsEntered();
		}
	}
	else {
		this->state->onControlsEntered();
	}
}

RenderableModel* Controls::getItem()
{
	return nullptr;
}
