#pragma once
#include "ActionActivation.h"

class ToggleActionActivation : public ActionActivation {
private:
	bool active;
public:
	ToggleActionActivation();
	//toggle doesn't care about release (theoretically it could react on release instead of on press)
	virtual Action onPress() override;

};
