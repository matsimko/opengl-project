#pragma once
#include "Command.h"
#include <glm/vec3.hpp>

class CircularMovementCommand :
    public Command
{
private:
    glm::vec3 centerPos;
    glm::vec3 startPos; //radius = dist(centerPos, startPos)

    enum State {
        SELECT_CENTER,
        SELECT_RADIUS
    };
    State state;

public:
    CircularMovementCommand(std::vector<Input*> inputs, ActionActivation* actionActivation);

    // Inherited via Command
    virtual void onActionStart() override;

    virtual void onActionEnd() override;

};

