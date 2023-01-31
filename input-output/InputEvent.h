#pragma once
#include "InputType.h"
#include "InputState.h"

struct InputEvent {
	InputType type;
	int key;
	InputState state;
};
