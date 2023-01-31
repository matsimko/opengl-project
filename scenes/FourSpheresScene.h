#pragma once
#include "SceneWithPlayerView.h"
#include "RenderableModel.h"

class FourSpheresScene : public SceneWithPlayerView {
private:
	RenderableModel* spheres[4];

public:
	~FourSpheresScene();
	virtual void doLoad() override;
	virtual void update(double dt) override;

};
