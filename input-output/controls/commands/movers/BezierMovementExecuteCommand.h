#pragma once
#include "Command.h"
#include "BezierMovementAddPointCommand.h"

class BezierMovementExecuteCommand :
    public Command
{
private:
    BezierMovementAddPointCommand* pointCmd;

public:
    BezierMovementExecuteCommand(std::vector<Input*> inputs, ActionActivation* actionActivation, BezierMovementAddPointCommand* pointCmd);

    // Inherited via Command
    virtual void onActionStart() override;
    virtual void onActionEnd() override;
};

