#include "BezierMovementAddPointCommand.h"
#include "App.h"

BezierMovementAddPointCommand::BezierMovementAddPointCommand(std::vector<Input*> inputs, ActionActivation* actionActivation)
	: Command(inputs, actionActivation)
{

}

void BezierMovementAddPointCommand::onActionStart()
{
	Scene* scene = App::getInstance().getScene();
	glm::vec3 point = scene->getWorldSpacePosAtCursor();
	points.push_back(point);
}

void BezierMovementAddPointCommand::onActionEnd()
{
}

std::vector<glm::vec3> BezierMovementAddPointCommand::getPoints()
{
	return points;
}

void BezierMovementAddPointCommand::clearPoints()
{
	points.clear();
}
