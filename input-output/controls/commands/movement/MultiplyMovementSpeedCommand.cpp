#include "MultiplyMovementSpeedCommand.h"

void MultiplyMovementSpeedCommand::onActionStart()
{
	playerView->setMovementSpeed(playerView->getMovementSpeed() * multiplier);
}

void MultiplyMovementSpeedCommand::onActionEnd()
{
	playerView->setMovementSpeed(playerView->getMovementSpeed() / multiplier);
}

MultiplyMovementSpeedCommand::MultiplyMovementSpeedCommand(std::vector<Input*> inputs, ActionActivation* actionActivation,
	PlayerView* playerView, float multiplier)
	: Command(inputs, actionActivation)
{
	this->playerView = playerView;
	this->multiplier = multiplier;
}
