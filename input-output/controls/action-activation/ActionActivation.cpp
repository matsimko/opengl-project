#include "ActionActivation.h"
#include <GL/glew.h>
#include "GLFW/glfw3.h"

Action ActionActivation::onPress()
{
    return Action::NONE;
}

Action ActionActivation::onRelease()
{
    return Action::NONE;
}

Action ActionActivation::process(InputState inputState)
{
    if (inputState == InputState::PRESSED) {
        return onPress();
    }
    else {
        return onRelease();
    }
}

Action ActionActivation::onControlsLeft()
{
    return Action::NONE;
}

Action ActionActivation::onControlsEntered(InputState inputState)
{
    return Action::NONE;
}

