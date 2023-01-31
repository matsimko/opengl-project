#pragma once
#include "Scene.h"
#include "PlayerView.h"

class SceneWithPlayerView : public Scene {
private:
	PlayerView* playerView;
protected:
	PlayerView* getPlayerView();

public:
	SceneWithPlayerView();
	~SceneWithPlayerView();

	// Inherited via Scene
	virtual void doLoad() override;
};

