#pragma once
#include "CancellableState.h"
class StraightMovementState :
    public CancellableState
{
public:
    StraightMovementState(Controls* controls);
};

