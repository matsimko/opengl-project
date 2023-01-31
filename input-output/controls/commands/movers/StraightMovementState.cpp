#include "StraightMovementState.h"
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "TapActionActivation.h"
#include "StraightMovementCommand.h"

StraightMovementState::StraightMovementState(Controls* controls)
	: CancellableState(controls) {
	Command* cmd = nullptr;
	std::vector<Input*> inputs;

	inputs = { Input::newMouseButtonInput(GLFW_MOUSE_BUTTON_1) };
	cmd = new StraightMovementCommand(inputs, new TapActionActivation());
	addCommand(cmd);
}
