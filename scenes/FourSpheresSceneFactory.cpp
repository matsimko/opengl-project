#include "FourSpheresSceneFactory.h"
#include "FourSpheresScene.h"

Scene* FourSpheresSceneFactory::newScene()
{
	return new FourSpheresScene();
}
