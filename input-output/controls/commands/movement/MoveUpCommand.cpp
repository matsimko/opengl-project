#include "MoveUpCommand.h"

void MoveUpCommand::onActionStart()
{
	playerView->addUpVel(1);
}

void MoveUpCommand::onActionEnd()
{
	playerView->addUpVel(-1);
}

MoveUpCommand::MoveUpCommand(std::vector<Input*> inputs, ActionActivation* actionActivation, PlayerView* playerView)
	: Command(inputs, actionActivation)
{
	this->playerView = playerView;
}
