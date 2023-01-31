#include "MoveBackwardCommand.h"

void MoveBackwardCommand::onActionStart()
{
	playerView->addForwardVel(-1);
}

void MoveBackwardCommand::onActionEnd()
{
	playerView->addForwardVel(1);
}

MoveBackwardCommand::MoveBackwardCommand(std::vector<Input*> inputs, ActionActivation* actionActivation, PlayerView* playerView)
	: Command(inputs, actionActivation)
{
	this->playerView = playerView;
}
