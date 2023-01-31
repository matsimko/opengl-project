#include "BezierMovementState.h"
#include "BezierMovementAddPointCommand.h"
#include "BezierMovementExecuteCommand.h"
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "TapActionActivation.h"

BezierMovementState::BezierMovementState(Controls* controls)
	: CancellableState(controls)
{
	std::vector<Input*> inputs;

	inputs = { Input::newMouseButtonInput(GLFW_MOUSE_BUTTON_1) };
	BezierMovementAddPointCommand* addPointCmd = new BezierMovementAddPointCommand(inputs, new TapActionActivation());
	addCommand(addPointCmd);

	inputs = { Input::newKeyInput(GLFW_KEY_X) };
	Command* executeCommand = new BezierMovementExecuteCommand(inputs, new TapActionActivation(), addPointCmd);
	addCommand(executeCommand);
}
