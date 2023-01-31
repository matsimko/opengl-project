#pragma once
#include "Command.h"
#include "PlayerView.h"

class MoveBackwardCommand : public Command {
private:
	PlayerView* playerView;
protected:
	// Inherited via Command
	virtual void onActionStart() override;
	virtual void onActionEnd() override;

public:
	MoveBackwardCommand(std::vector<Input*> inputs, ActionActivation* actionActivation, PlayerView* playerView);
};
