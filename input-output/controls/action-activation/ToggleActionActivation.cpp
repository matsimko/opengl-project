#include "ToggleActionActivation.h"

ToggleActionActivation::ToggleActionActivation()
{
    this->active = false;
}

Action ToggleActionActivation::onPress()
{
    Action action = (active) ? Action::END : Action::START;
    active = !active;
    return action;
}
