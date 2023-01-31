#pragma once
#include "Scene.h"

//(factory method pattern) - the App class won't be dependent on the concrete scene(s), because it doesn't need to explicitly create them
class SceneFactory {
private:
	static SceneFactory* instance;
protected:
	SceneFactory();

public:
	//this might return a std::vector later on
	virtual Scene* newScene() = 0;

	static SceneFactory& getInstance();
	static void deleteInstance();
};
