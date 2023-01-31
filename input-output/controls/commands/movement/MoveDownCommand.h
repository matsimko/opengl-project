#pragma once
#include "Command.h"
#include "PlayerView.h"

class MoveDownCommand : public Command {
private:
	PlayerView* playerView;
protected:
	// Inherited via Command
	virtual void onActionStart() override;
	virtual void onActionEnd() override;

public:
	MoveDownCommand(std::vector<Input*> inputs, ActionActivation* actionActivation, PlayerView* playerView);
};
