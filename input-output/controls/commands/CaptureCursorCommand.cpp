#include "CaptureCursorCommand.h"

void CaptureCursorCommand::onActionStart()
{
	app.getWindow()->captureCursor();
}

void CaptureCursorCommand::onActionEnd()
{
	app.getWindow()->releaseCursor();
}

CaptureCursorCommand::CaptureCursorCommand(std::vector<Input*> inputs, ActionActivation* actionActivation)
	: Command(inputs, actionActivation), app(App::getInstance())
{

}
