#pragma once
#include "Scene.h"

/*This disadvantage of this approach is that there is only one instance of a scene that can be retrieved,
* so I would need to make copies of the scene everytime a new is requested. This is more of a Prototype pattern.
* I don't want the App to know which scene is being used, so there are probably no other reasonable options than those two.
* */
class AlternativeSceneFactory {
private:
	static Scene* scene;

public:

	static void setScene(Scene* scene);
	static Scene* getScene();
	static void deleteScene();
};
