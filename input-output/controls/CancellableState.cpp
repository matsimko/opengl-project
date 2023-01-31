#include "CancellableState.h"
#include "ChangeStateCommand.h"
#include "TapActionActivation.h"

CancellableState::CancellableState(Controls* controls)
 : ControlsState(controls) {
	Command* cmd = nullptr;
	std::vector<Input*> inputs;

	inputs = { Input::newKeyInput(GLFW_KEY_C) };
	cmd = new ChangeStateCommand(inputs, new TapActionActivation(), nullptr);
	addCommand(cmd);
}
