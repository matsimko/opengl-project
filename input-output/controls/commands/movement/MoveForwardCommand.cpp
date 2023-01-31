#include "MoveForwardCommand.h"

void MoveForwardCommand::onActionStart()
{
	playerView->addForwardVel(1);
}

void MoveForwardCommand::onActionEnd()
{
	playerView->addForwardVel(-1);
}

MoveForwardCommand::MoveForwardCommand(std::vector<Input*> inputs, ActionActivation* actionActivation, PlayerView* playerView)
	: Command(inputs, actionActivation)
{
	this->playerView = playerView;
}
