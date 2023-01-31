#pragma once
#include "Command.h"
#include <glm/vec3.hpp>
#include <vector>

class BezierMovementAddPointCommand :
    public Command
{
private:
    std::vector<glm::vec3> points;
public:
    BezierMovementAddPointCommand(std::vector<Input*> inputs, ActionActivation* actionActivation);

    // Inherited via Command
    virtual void onActionStart() override;
    virtual void onActionEnd() override;

    std::vector<glm::vec3> getPoints();
    void clearPoints();
};

