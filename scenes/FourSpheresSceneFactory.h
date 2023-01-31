#pragma once
#include "SceneFactory.h"


class FourSpheresSceneFactory : public SceneFactory {
	// Inherited via SceneFactory
	virtual Scene* newScene() override;
};

