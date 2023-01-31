#pragma once
#include "InputEvent.h"

class InputListener {

public:
	virtual void onInput(InputEvent e) = 0;
};
