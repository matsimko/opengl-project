#include "MoveRightCommand.h"

void MoveRightCommand::onActionStart()
{
	playerView->addRightVel(1);
}

void MoveRightCommand::onActionEnd()
{
	playerView->addRightVel(-1);
}

MoveRightCommand::MoveRightCommand(std::vector<Input*> inputs, ActionActivation* actionActivation, PlayerView* playerView)
	: Command(inputs, actionActivation)
{
	this->playerView = playerView;
}
