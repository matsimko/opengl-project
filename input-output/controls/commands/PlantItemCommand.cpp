#include "PlantItemCommand.h"
#include "Scene.h"
#include "Window.h"
#include "Controls.h"


void PlantItemCommand::onActionStart()
{
	Scene* scene = App::getInstance().getScene();
	glm::vec3 pos = scene->getWorldSpacePosAtCursor();

	RenderableModel* obj = scene->getControls()->getItem()->clone();
	scene->addRenderableModel(obj);
	obj->resetTranslation();
	obj->translateLast(pos.x, pos.y, pos.z); //translate last in case scaling was done
}

void PlantItemCommand::onActionEnd()
{
}


PlantItemCommand::PlantItemCommand(std::vector<Input*> inputs, ActionActivation* actionActivation)
	: Command(inputs, actionActivation)
{

}
