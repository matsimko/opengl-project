#pragma once
#include "SceneWithPlayerView.h"
#include "RenderableModel.h"

class MultipleShadersScene : public SceneWithPlayerView {
private:
	RenderableModel* spheres[4];
	RenderableModel* texturedPlains[3];

public:
	~MultipleShadersScene();
	virtual void doLoad() override;
	virtual void update(double dt) override;
};
