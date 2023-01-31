#pragma once
#include "SceneWithPlayerView.h"
#include "RenderableModel.h"
#include "Skybox.h"
#include "Spotlight.h"
#include "Controls.h"

class ForestScene : public SceneWithPlayerView {
private:

	//2D grid of trees
	RenderableModel*** forest;
	int rows;
	int cols;
	float chanceOfTreeInCell;
	float cellSize;
	int positionDeviation;
	float treeSizeScaleMin;
	float treeSizeScaleMax;
	float treeHeightScaleMin;
	float treeHeightScaleMax;

	Spotlight* movingSpotlight;
	glm::vec3 movingSpotlightAnchor;

	Spotlight* flashlight;

public:
	ForestScene();
	~ForestScene();
	virtual void doLoad() override;
	virtual void update(double dt) override;
};
