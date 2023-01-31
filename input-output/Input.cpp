#include "Input.h"

Input::Input(InputType type, int key)
{
    this->type = type;
    this->key = key;
}

bool Input::isTriggered(InputEvent e)
{
    return e.type == type && e.key == key;
}


Input* Input::newMouseButtonInput(int button)
{
    return new Input(InputType::MouseButton, button);
}

Input* Input::newKeyInput(int key)
{
    return new Input(InputType::Key, key);
}

InputType Input::getType()
{
    return type;
}

int Input::getKey()
{
    return key;
}
