#include "CircularMovementState.h"
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "CircularMovementCommand.h"
#include "TapActionActivation.h"

CircularMovementState::CircularMovementState(Controls* controls)
 : CancellableState(controls) {
	Command* cmd = nullptr;
	std::vector<Input*> inputs;

	inputs = { Input::newMouseButtonInput(GLFW_MOUSE_BUTTON_1) };
	cmd = new CircularMovementCommand(inputs, new TapActionActivation());
	addCommand(cmd);
}
