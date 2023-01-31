#include "AlternativeSceneFactory.h"
#include "MultipleShadersScene.h"
#include "ForestScene.h"

//Scene* AlternativeSceneFactory::scene = new MultipleShadersScene();
Scene* AlternativeSceneFactory::scene = nullptr;

void AlternativeSceneFactory::setScene(Scene* scene)
{
	scene = scene;
}

Scene* AlternativeSceneFactory::getScene()
{
	return scene;
}

void AlternativeSceneFactory::deleteScene()
{
	delete scene;
	scene = nullptr;
}
