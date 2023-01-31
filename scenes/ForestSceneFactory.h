#pragma once
#include "SceneFactory.h"

class ForestSceneFactory : public SceneFactory {
	// Inherited via SceneFactory
	virtual Scene* newScene() override;
};