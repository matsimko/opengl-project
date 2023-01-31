#pragma once
#include "Controls.h"
#include "RenderableModel.h"

class DefaultControls : public Controls {
private:
	RenderableModel* item;
public:
	DefaultControls(PlayerView* playerView, RenderableModel* item);
	~DefaultControls();

	RenderableModel* getItem() override;
};
