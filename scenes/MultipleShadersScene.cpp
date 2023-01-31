#include "MultipleShadersScene.h"
#include "App.h"
#include "texturedPlain.h"
#include "sphere.h"

#include "PointLight.h"
#include "ModelWithPositionNormalUv.h"
#include "ModelWithPositionNormal.h"

MultipleShadersScene::~MultipleShadersScene()
{
	for (int i = 0; i < 4; i++) {
		delete spheres[i];
	}
	delete[] spheres;
	for (int i = 0; i < 3; i++) {
		delete texturedPlains[i];
	}
	delete[] texturedPlains;
}

void MultipleShadersScene::doLoad()
{
	SceneWithPlayerView::doLoad();

	ShaderProgram* phong = App::getInstance().
		getShaderManager()->getShaderProgram(ShaderManager::PHONG);
	ShaderProgram* lambert = App::getInstance().
		getShaderManager()->getShaderProgram(ShaderManager::LAMBERT);
	ShaderProgram* constant = App::getInstance().
		getShaderManager()->getShaderProgram(ShaderManager::CONSTANT);
	ShaderProgram* shaders[4];
	addShaderProgram(phong);
	addShaderProgram(lambert);
	addShaderProgram(constant);
	shaders[0] = phong;
	shaders[1] = lambert;
	shaders[2] = constant;
	shaders[3] = shaders[0];

	camera->translate(MovementVector(-8, 0, 0));
	PointLight* pointLight = new PointLight(glm::vec3(0.f, 0.f, 0.f));
	lights->addLight(pointLight);

	Model* sphereModel = new ModelWithPositionNormal(sphere, SPHERE_SIZE);
	sphereModel->load();
	for (int i = 0; i < 4; i++) {
		spheres[i] = new RenderableModel(sphereModel, shaders[i]);
		addRenderable(spheres[i]);
	}

	Texture* plainTexture = Texture::getTexture("test.png");
	Model* plainModel = new ModelWithPositionNormalUv(texturedPlain, TEXTURED_PLAIN_SIZE, plainTexture);
	plainModel->load();
	for (int i = 0; i < 3; i++) {
		texturedPlains[i] = new RenderableModel(plainModel, shaders[i]);	
		addRenderable(texturedPlains[i]);
	}

	float dist = 3;
	spheres[0]->translate(dist, 0, 0);
	spheres[1]->translate(-dist, 0, 0);
	spheres[2]->translate(0, dist, 0);
	spheres[3]->translate(0, -dist, 0);

	dist = 2;
	texturedPlains[0]->translate(dist, 0, 0);
	texturedPlains[0]->rotateDegrees(90, 0, 0, 1);

	texturedPlains[1]->translate(-dist, 0, 0);
	texturedPlains[1]->rotateDegrees(-90, 0, 0, 1);
	texturedPlains[2]->translate(0, dist, 0);

}

void MultipleShadersScene::update(double dt)
{
	SceneWithPlayerView::update(dt);
}
