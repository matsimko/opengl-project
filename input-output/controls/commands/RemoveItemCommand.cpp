#include "RemoveItemCommand.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Scene.h"
#include "Window.h"


void RemoveItemCommand::onActionStart()
{
	StencilObjectFinder& stencilFinder = app.getWindow()->getStencilObjectFinder();
	GLuint id = stencilFinder.getIdAtCursor();

	IdentifiableObject* obj = IdentifiableObject::getObjectById(id);
	if (obj != nullptr) {
		RenderableModel* renderableModel = dynamic_cast<RenderableModel*>(obj);

		if (renderableModel) {
			app.getScene()->removeRenderableModel(renderableModel);
		}
		else {
			app.getScene()->removeRenderable(obj);
		}
		
		IdentifiableObject::removeObjectById(id);
	}
}

void RemoveItemCommand::onActionEnd()
{
}


RemoveItemCommand::RemoveItemCommand(std::vector<Input*> inputs, ActionActivation* actionActivation)
	: Command(inputs, actionActivation), app(App::getInstance())
{

}
