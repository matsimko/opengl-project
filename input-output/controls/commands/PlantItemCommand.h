#pragma once
#include "Command.h"
#include "App.h"
#include "RenderableModel.h"
#include "PlayerView.h"

class PlantItemCommand : public Command {
private:
protected:
	// Inherited via Command
	virtual void onActionStart() override;
	virtual void onActionEnd() override;
public:
	PlantItemCommand(std::vector<Input*> inputs, ActionActivation* actionActivation);
};
