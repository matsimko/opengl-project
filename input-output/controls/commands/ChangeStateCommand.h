#pragma once
#include "Command.h"
#include "ControlsState.h"
#include "Controls.h"

class ChangeStateCommand :
    public Command
{
private:
    ControlsState* state;
public:
    ChangeStateCommand(std::vector<Input*> inputs, ActionActivation* actionActivation, ControlsState* state);

    // Inherited via Command
    virtual void onActionStart() override;
    virtual void onActionEnd() override;
};

