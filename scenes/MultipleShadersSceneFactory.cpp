#include "MultipleShadersSceneFactory.h"
#include "MultipleShadersScene.h"

Scene* MultipleShadersSceneFactory::newScene()
{
    return new MultipleShadersScene();
}
