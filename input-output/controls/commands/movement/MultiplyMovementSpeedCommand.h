#pragma once
#include "Command.h"
#include "PlayerView.h"

class MultiplyMovementSpeedCommand : public Command {
private:
	PlayerView* playerView;
	float multiplier;
protected:
	// Inherited via Command
	virtual void onActionStart() override;
	virtual void onActionEnd() override;

public:
	MultiplyMovementSpeedCommand(std::vector<Input*> inputs, ActionActivation* actionActivation, PlayerView* playerView, float multiplier);
};
