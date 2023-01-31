#include "ForestSceneFactory.h"
#include "ForestScene.h"

Scene* ForestSceneFactory::newScene()
{
    return new ForestScene();
}
