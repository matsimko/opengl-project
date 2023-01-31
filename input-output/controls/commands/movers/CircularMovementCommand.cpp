#include "CircularMovementCommand.h"
#include "App.h"
#include "CircularMover.h"

CircularMovementCommand::CircularMovementCommand(std::vector<Input*> inputs, ActionActivation* actionActivation)
	:Command(inputs, actionActivation)
{
	this->state = SELECT_CENTER;
}

void CircularMovementCommand::onActionStart()
{
	Scene* scene = App::getInstance().getScene();

	if (state == SELECT_CENTER) {
		centerPos = scene->getWorldSpacePosAtCursor();
		state = SELECT_RADIUS;
	}
	else {
		startPos = scene->getWorldSpacePosAtCursor();
		RenderableModel* item = scene->getControls()->getItem()->clone();
		item->setUpdatable(new CircularMover(centerPos, startPos, item));
		scene->addRenderableModel(item);
		state = SELECT_CENTER;
		scene->getControls()->setState(nullptr);
	}
}

void CircularMovementCommand::onActionEnd()
{
}
