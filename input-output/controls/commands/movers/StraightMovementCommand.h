#pragma once
#include "Command.h"
#include "glm/vec3.hpp"

class StraightMovementCommand :
    public Command
{
private:
    glm::vec3 startPos;
    glm::vec3 endPos;

    enum State {
        START_POS,
        END_POS,
    };
    State state;


public:
    StraightMovementCommand(std::vector<Input*> inputs, ActionActivation* actionActivation);

    // Inherited via Command
    virtual void onActionStart() override;
    virtual void onActionEnd() override;
};

