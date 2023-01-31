#pragma once
#include "ControlsState.h"

class CancellableState : public ControlsState {
public:
	CancellableState(Controls* controls);
};
