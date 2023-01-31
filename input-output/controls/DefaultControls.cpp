#include "DefaultControls.h"
#include "MoveForwardCommand.h"
#include "MoveBackwardCommand.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "MoveUpCommand.h"
#include "MoveDownCommand.h"
#include "PlantItemCommand.h"
#include "RemoveItemCommand.h"
#include "CaptureCursorCommand.h"
#include "QuitCommand.h"
#include "MultiplyMovementSpeedCommand.h"

#include "HoldActionActivation.h"
#include "ToggleActionActivation.h"
#include "TapActionActivation.h"
#include "ChangeStateCommand.h"
#include "CircularMovementState.h"
#include "StraightMovementState.h"
#include "BezierMovementState.h"

DefaultControls::DefaultControls(PlayerView* playerView, RenderableModel* item)
{
	this->item = item;

	//normally it would be read from a config file or whatever (and there could potentially be multiple sets of controls)
	Command* cmd = nullptr;
	std::vector<Input*> inputs;

	inputs = { Input::newKeyInput(GLFW_KEY_ESCAPE) };
	cmd = new QuitCommand(inputs);
	addCommand(cmd);

	inputs = { Input::newKeyInput(GLFW_KEY_W), Input::newKeyInput(GLFW_KEY_UP) };
	cmd = new MoveForwardCommand(inputs, new HoldActionActivation(), playerView);
	addCommand(cmd);

	inputs = { Input::newKeyInput(GLFW_KEY_S), Input::newKeyInput(GLFW_KEY_DOWN) };
	cmd = new MoveBackwardCommand(inputs, new HoldActionActivation(), playerView);
	addCommand(cmd);

	inputs = { Input::newKeyInput(GLFW_KEY_D), Input::newKeyInput(GLFW_KEY_RIGHT) };
	cmd = new MoveRightCommand(inputs, new HoldActionActivation(), playerView);
	addCommand(cmd);

	inputs = { Input::newKeyInput(GLFW_KEY_A), Input::newKeyInput(GLFW_KEY_LEFT) };
	cmd = new MoveLeftCommand(inputs, new HoldActionActivation(), playerView);
	addCommand(cmd);

	inputs = { Input::newKeyInput(GLFW_KEY_SPACE) };
	cmd = new MoveUpCommand(inputs, new HoldActionActivation(), playerView);
	addCommand(cmd);

	inputs = { Input::newKeyInput(GLFW_KEY_LEFT_CONTROL) };
	cmd = new MoveDownCommand(inputs, new HoldActionActivation(), playerView);
	addCommand(cmd);

	inputs = { Input::newKeyInput(GLFW_KEY_LEFT_SHIFT) };
	cmd = new MultiplyMovementSpeedCommand(inputs, new ToggleActionActivation(), playerView, 3.f);
	addCommand(cmd);

	//if I wanted another actionActivation than tap, the player would have to have a state "plantingItems" and "removingItems",
	//similarly to a "shooting" state
	inputs = { Input::newMouseButtonInput(GLFW_MOUSE_BUTTON_2) };
	cmd = new CaptureCursorCommand(inputs, new ToggleActionActivation());
	addCommand(cmd);

	inputs = { Input::newKeyInput(GLFW_KEY_E) };
	cmd = new PlantItemCommand(inputs, new TapActionActivation());
	addCommand(cmd);

	inputs = { Input::newKeyInput(GLFW_KEY_Q) };
	cmd = new RemoveItemCommand(inputs, new TapActionActivation());
	addCommand(cmd);

	inputs = { Input::newKeyInput(GLFW_KEY_1) };
	cmd = new ChangeStateCommand(inputs, new TapActionActivation(), new CircularMovementState(this));
	addCommand(cmd);

	inputs = { Input::newKeyInput(GLFW_KEY_2) };
	cmd = new ChangeStateCommand(inputs, new TapActionActivation(), new StraightMovementState(this));
	addCommand(cmd);

	inputs = { Input::newKeyInput(GLFW_KEY_3) };
	cmd = new ChangeStateCommand(inputs, new TapActionActivation(), new BezierMovementState(this));
	addCommand(cmd);
}

DefaultControls::~DefaultControls()
{
	delete item;
}

RenderableModel* DefaultControls::getItem()
{
	return item;
}
