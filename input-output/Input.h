#pragma once
#include "InputEvent.h"
#include <string>

//represents either a key or mouse event (I could make 2 subclasses instead of using "type")
//each Command can potentially have multiple inputs that activate it.
//(It would be too time consuming to make a custom enum or constants to represent both keys and mouse buttons uniformly, so I am keeping the GLFW stuff.)
class Input {

private:
	InputType type;
	int key;

	Input(InputType type, int key);

public:
	bool isTriggered(InputEvent e);

	//"factory methods"
	static Input* newMouseButtonInput(int button);
	static Input* newKeyInput(int key);

	InputType getType();
	int getKey();
};
