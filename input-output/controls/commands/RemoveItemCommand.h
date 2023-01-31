#pragma once

#include "Command.h"
#include "App.h"
#include "RenderableModel.h"
#include "PlayerView.h"

class RemoveItemCommand : public Command {
private:
	App& app;
protected:
	// Inherited via Command
	virtual void onActionStart() override;
	virtual void onActionEnd() override;
public:
	RemoveItemCommand(std::vector<Input*> inputs, ActionActivation* actionActivation);

};