#include "FourSpheresScene.h"
#include "App.h"
#include "sphere.h"
#include "PointLight.h"

#include "ModelWithPositionNormal.h"

FourSpheresScene::~FourSpheresScene()
{
	for (int i = 0; i < 4; i++) {
		delete spheres[i];
	}
	delete[] spheres;
}

void FourSpheresScene::doLoad()
{
	SceneWithPlayerView::doLoad();

	ShaderProgram* shader = App::getInstance().
		getShaderManager()->getShaderProgram(ShaderManager::PHONG);
	addShaderProgram(shader);
	camera->translate(MovementVector(-8, 0, 0));
	PointLight* pointLight = new PointLight(glm::vec3(0.f,0.f,0.f));
	lights->addLight(pointLight);

	Model* sphereModel = new ModelWithPositionNormal(sphere, SPHERE_SIZE);
	sphereModel->load();

	for (int i = 0; i < 4; i++) {
		spheres[i] = new RenderableModel(sphereModel, shader);
		addRenderable(spheres[i]);
	}


	float dist = 3;
	spheres[0]->translate(dist,0,0);
	spheres[1]->translate(-dist,0,0);
	spheres[2]->translate(0, dist, 0);
	spheres[3]->translate(0, -dist, 0);

}

void FourSpheresScene::update(double dt)
{
	SceneWithPlayerView::update(dt);
}
