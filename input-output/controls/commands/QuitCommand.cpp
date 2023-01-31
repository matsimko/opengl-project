#include "QuitCommand.h"
#include "App.h"
#include "TapActionActivation.h"

void QuitCommand::onActionStart()
{
	App::getInstance().quit();
}

void QuitCommand::onActionEnd()
{
}

QuitCommand::QuitCommand(std::vector<Input*> inputs)
	: Command(inputs, new TapActionActivation())
{

}
