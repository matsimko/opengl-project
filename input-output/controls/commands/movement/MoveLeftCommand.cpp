#include "MoveLeftCommand.h"

void MoveLeftCommand::onActionStart()
{
	playerView->addRightVel(-1);
}

void MoveLeftCommand::onActionEnd()
{
	playerView->addRightVel(1);
}

MoveLeftCommand::MoveLeftCommand(std::vector<Input*> inputs, ActionActivation* actionActivation, PlayerView* playerView)
	: Command(inputs, actionActivation)
{
	this->playerView = playerView;
}
