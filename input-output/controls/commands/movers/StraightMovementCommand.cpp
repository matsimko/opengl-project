#include "StraightMovementCommand.h"
#include "App.h"
#include "StraightMover.h"


StraightMovementCommand::StraightMovementCommand(std::vector<Input*> inputs, ActionActivation* actionActivation)
	: Command(inputs, actionActivation)
{
	state = START_POS;
}

void StraightMovementCommand::onActionStart()
{
	Scene* scene = App::getInstance().getScene();

	if (state == START_POS) {
		startPos = scene->getWorldSpacePosAtCursor();
		state = END_POS;
	}
	else {
		endPos = scene->getWorldSpacePosAtCursor();
		RenderableModel* item = scene->getControls()->getItem()->clone();
		item->setUpdatable(new StraightMover(startPos, endPos, item));
		scene->addRenderableModel(item);
		state = START_POS;
		scene->getControls()->setState(nullptr);
	}
}

void StraightMovementCommand::onActionEnd()
{
}
