#pragma once
#include "SceneFactory.h"

class MultipleShadersSceneFactory : public SceneFactory {
	// Inherited via SceneFactory
	virtual Scene* newScene() override;
};