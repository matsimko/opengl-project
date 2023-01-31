#pragma once
#include "ActionActivation.h"

class HoldActionActivation : public ActionActivation {
private:
	bool started;

public:
	HoldActionActivation();

	virtual Action onPress() override;
	virtual Action onRelease() override;

	virtual Action onControlsLeft() override;
	virtual Action onControlsEntered(InputState inputState) override;
};
