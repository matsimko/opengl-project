#pragma once

#include "ActionActivation.h"
//one-time activation
class TapActionActivation : public ActionActivation {
public:
	//tap doesn't care about release (theoretically it could react on release instead of on press)
	virtual Action onPress() override;

};
