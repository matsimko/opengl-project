#pragma once
#include "Camera.h"
#include "Renderable.h"
#include "Loadable.h"
#include "Updatable.h"
#include "Lights.h"
#include "Background.h"
#include "UI.h"
#include "RenderableModel.h"
#include "Controls.h"


class App;

class Scene : public Loadable, public Updatable, public Renderable {
private:
	App& app;
	//Incidentally, the scene acts like a composite of Updatables/Renderables. (composite pattern)
	//Therefore, a scene contain subscenes.

	std::vector<Renderable*> renderables;
	std::vector<Updatable*> updatables;
	std::vector<ShaderProgram*> shaderPrograms;

	Background* background;
	Controls* controls;

protected:
	Lights* lights;
	//this could be refactored in case of multiple cameras (for now I am just adding camera listeners in addShaderProgram and setBackground)
	Camera* camera; 
	UI* ui;
	Scene();

	void addShaderProgram(ShaderProgram* shaderProgram);
	void setBackground(Background* background);
	void setControls(Controls* controls);

	virtual void doLoad() = 0;

public:
	//Add a Renderable that is to be rendered in the scene each frame
	void addRenderable(Renderable* renderable);
	void removeRenderable(Renderable* renderable);
	//Add an Updatable that is to be updated each frame
	void addUpdatable(Updatable* updatable);
	void removeUpdatable(Updatable* updatable);

	void addRenderableModel(RenderableModel* renderableModel);
	void removeRenderableModel(RenderableModel* renderableModel);

	virtual void render() override;
	//template method
	virtual void load() override;

	Camera* getCamera();
	~Scene();

	// Inherited via Updatable
	virtual void update(double dt) override;

	glm::vec3 getWorldSpacePosAtCursor();
	Controls* getControls();
};
