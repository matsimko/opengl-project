#include "HoldActionActivation.h"

HoldActionActivation::HoldActionActivation()
{
    started = false;
}

Action HoldActionActivation::onPress()
{
    if (!started) {
        started = true;
        return Action::START;
    }
    
}

Action HoldActionActivation::onRelease()
{
    if (started) { //the if is needed in case the key was held in another ControlsState and only released in the current state
        started = false;
        return Action::END;
    }
    
}

Action HoldActionActivation::onControlsLeft()
{
    if (started) {
        started = false;
        return Action::END;
    }
}

Action HoldActionActivation::onControlsEntered(InputState inputState)
{
    if (inputState == InputState::PRESSED) {
        return onPress();
    }
    return Action::NONE;
}
