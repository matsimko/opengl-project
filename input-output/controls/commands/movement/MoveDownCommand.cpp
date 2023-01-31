#include "MoveDownCommand.h"

void MoveDownCommand::onActionStart()
{
	playerView->addUpVel(-1);
}

void MoveDownCommand::onActionEnd()
{
	playerView->addUpVel(1);
}

MoveDownCommand::MoveDownCommand(std::vector<Input*> inputs, ActionActivation* actionActivation, PlayerView* playerView)
	: Command(inputs, actionActivation)
{
	this->playerView = playerView;
}
