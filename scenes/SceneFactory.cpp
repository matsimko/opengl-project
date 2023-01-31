#include "SceneFactory.h"
#include "FourSpheresSceneFactory.h"
#include "ForestSceneFactory.h"
#include "MultipleShadersSceneFactory.h"

SceneFactory* SceneFactory::instance = nullptr;

SceneFactory::SceneFactory()
{
}

SceneFactory& SceneFactory::getInstance()
{
    if (!instance) {
        //change this code to change the concrete factory (having setInstance method to allow dynamic change is not needed now)
        instance = new ForestSceneFactory();
    }

    return *instance;
}

void SceneFactory::deleteInstance()
{
    delete instance;
}
