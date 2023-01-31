#pragma once
#include "CancellableState.h"
class BezierMovementState :
    public CancellableState
{
public:
    BezierMovementState(Controls* controls);
};

