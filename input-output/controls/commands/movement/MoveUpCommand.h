#pragma once
#include "Command.h"
#include "PlayerView.h"

class MoveUpCommand : public Command {
private:
	PlayerView* playerView;
protected:
	// Inherited via Command
	virtual void onActionStart() override;
	virtual void onActionEnd() override;

public:
	MoveUpCommand(std::vector<Input*> inputs, ActionActivation* actionActivation, PlayerView* playerView);
};
