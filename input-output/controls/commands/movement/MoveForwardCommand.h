#pragma once
#include "Command.h"
#include "PlayerView.h"

class MoveForwardCommand : public Command {
private:
	PlayerView* playerView;
protected:
	// Inherited via Command
	virtual void onActionStart() override;
	virtual void onActionEnd() override;

public:
	MoveForwardCommand(std::vector<Input*> inputs, ActionActivation* actionActivation, PlayerView* playerView);
};
