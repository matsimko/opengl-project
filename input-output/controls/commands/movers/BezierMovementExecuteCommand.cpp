#include "BezierMovementExecuteCommand.h"
#include "App.h"
#include "BezierMover.h"

BezierMovementExecuteCommand::BezierMovementExecuteCommand(std::vector<Input*> inputs, ActionActivation* actionActivation,
	BezierMovementAddPointCommand* pointCmd)
	: Command(inputs, actionActivation)
{
	this->pointCmd = pointCmd;
}

void BezierMovementExecuteCommand::onActionStart()
{
	std::vector<glm::vec3> points = pointCmd->getPoints(); //this makes a copy of the vector
	if (points.size() >= 2) {
		Scene* scene = App::getInstance().getScene();
		RenderableModel* item = scene->getControls()->getItem()->clone();
		item->setUpdatable(new BezierMover(points, item));
		scene->addRenderableModel(item);

		pointCmd->clearPoints();
		scene->getControls()->setState(nullptr);
	}
}

void BezierMovementExecuteCommand::onActionEnd()
{
}
