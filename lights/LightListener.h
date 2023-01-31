#pragma once
#include "Light.h"

class LightListener {
public:
	virtual void onLightPositionChanged(Light* light) = 0;
};
