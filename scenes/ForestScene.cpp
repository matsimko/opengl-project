#include "ForestScene.h"
#include "DefaultControls.h"
#include "App.h"
#include "ShaderManager.h"
#include "texturedPlain.h"
#include "RenderableModel.h"
#include "ShaderProgram.h"
#include "tree.h"
#include <stdlib.h>
#include <time.h>
#include "Utils.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include "PointLight.h"
#include "DirectionalLight.h"
#include "ModelManager.h"
#include "ModelWithPositionNormal.h"
#include "ModelWithPositionNormalUv.h"

#include "sky/skyboxVertices.h"
#include "Terrain.h"

ForestScene::ForestScene()
{
	rows = cols = 20;
	forest = new RenderableModel** [rows];
	for (int r = 0; r < rows; r++) {
		forest[r] = new RenderableModel*[cols];
		for (int c = 0; c < cols; c++) {
			forest[r][c] = nullptr;
		}
	}
	movingSpotlight = nullptr;
	chanceOfTreeInCell = 0.7;
	cellSize = 1.5f;
	positionDeviation = 1;
	treeHeightScaleMin = 1;
	treeHeightScaleMax = 2;
	treeSizeScaleMin = 1;
	treeSizeScaleMax = 2;
}

ForestScene::~ForestScene()
{
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			delete forest[r][c];
		}
		delete[] forest[r];
	}
	
	delete[] forest;
}

void ForestScene::doLoad()
{
	SceneWithPlayerView::doLoad();

	CubeMapFilenames cubeMapFileNames(
		"sky/cubemap/posx.jpg",
		"sky/cubemap/negx.jpg",
		"sky/cubemap/posy.jpg",
		"sky/cubemap/negy.jpg",
		"sky/cubemap/posz.jpg",
		"sky/cubemap/negz.jpg");
	setBackground(new Skybox(skyboxVertices, SKYBOX_VERTICES_SIZE, cubeMapFileNames));

	ShaderManager* shaderManager = App::getInstance().getShaderManager();
	ShaderProgram* phong = shaderManager->getShaderProgram(ShaderManager::PHONG);
	addShaderProgram(phong);
	ShaderProgram* lambert = shaderManager->getShaderProgram(ShaderManager::LAMBERT);
	addShaderProgram(lambert);

	camera->translate(MovementVector(-8, 0, 10));

	Light* pointLight = new PointLight(glm::vec3(0.f, 10.f, 10.f), glm::vec4(0.1f, 0.1f, 0.1f, 1.0f), glm::vec4(1.f, 0.2f, 0.2f, 1.0f));
	lights->addLight(pointLight);
	Light* dirLight = new DirectionalLight(glm::vec3(2.f, -1.f, 0), glm::vec4(0.1f, 0.1f, 0.1f, 1.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.f));
	lights->addLight(dirLight);

	movingSpotlightAnchor = glm::vec3(cellSize * cols / 2.f, 10.f, cellSize * rows / 2.f);
	glm::vec3 movingSpotlightPos = movingSpotlightAnchor - glm::vec3(cellSize * cols / 2.f, 0, 0); //radius = cellSize * cols / 2.f
	movingSpotlight = new Spotlight(movingSpotlightPos);

	lights->addLight(movingSpotlight);

	//flashlight = new Spotlight(camera->getPos(), camera->getTarget(), 0.94f);
	//lights->addLight(flashlight);

	
	ModelManager* modelManager = App::getInstance().getModelManager();

	Model* plainModel = modelManager->loadModel("models/teren/teren.obj"); //modelManager->loadModel("models/plane/plane.obj");//
	RenderableModel* plain = new RenderableModel(plainModel, lambert);
	plain->scale(cellSize * rows * 3, 8, cellSize * cols * 3);
	addRenderable(plain);

	//float forrestWidth = cellSize * cols;
	//float tilesPerRow = 5;
	//Terrain* terrain = new Terrain(-forrestWidth, -forrestWidth, tilesPerRow * 3, tilesPerRow * 3, forrestWidth / tilesPerRow, plainModel, lambert);
	//addRenderable(terrain);
	

	Model* zombieModel = modelManager->loadModel("models/zombie/zombie.obj");
	RenderableModel* zombie = new RenderableModel(zombieModel, phong);
	addRenderableModel(zombie);
	zombie->translate(10, 0, -20);
	
	Model* houseModel = modelManager->loadModel("models/house/model.obj");
	RenderableModel* house = new RenderableModel(houseModel, phong);
	addRenderableModel(house);
	house->translate(30, 0, -20);
	house->scale(10, 10, 10); //make it 10 times bigger than unscaled models

	Model* sphereModel = modelManager->loadModel("models/sphere/model.obj", "models/sphere/albedo.png", "models/sphere/normalmap.png");
	RenderableModel* sphere = new RenderableModel(sphereModel, phong);
	addRenderableModel(sphere);
	sphere->translate(8, 0, -20);

	Model* sphereNoNormalMapModel = modelManager->loadModel("models/sphere/model.obj", "models/sphere/albedo.png");
	RenderableModel* sphereNoNormalMap = new RenderableModel(sphereNoNormalMapModel, phong);
	addRenderableModel(sphereNoNormalMap);
	sphereNoNormalMap->translate(5, 0, -20);

	Model* boxModel = modelManager->loadModel("models/box/model.obj", "models/box/albedo.png", "models/box/normalmap.png");
	RenderableModel* box = new RenderableModel(boxModel, phong);
	addRenderableModel(box);
	box->translate(2, 0, -20);

	Model* boxNoNormalMapModel = modelManager->loadModel("models/box/model.obj", "models/box/albedo.png");
	RenderableModel* boxNoNormalMap = new RenderableModel(boxNoNormalMapModel, phong);
	addRenderableModel(boxNoNormalMap);
	boxNoNormalMap->translate(-1, 0, -20);

	RenderableModel* boxLambert = new RenderableModel(boxModel, lambert);
	addRenderableModel(boxLambert);
	boxLambert->translate(-4, 0, -20);

	/*Model* treeModel = new ModelWithPositionNormal(tree, TREE_SIZE);
	treeModel->load*/
	Model* treeModel = modelManager->loadModel("models/tree/tree.obj");

	srand(time(NULL));
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (randZeroToOne() <= chanceOfTreeInCell) {
				RenderableModel* tree = new RenderableModel(treeModel, phong);
				addRenderableModel(tree);
				forest[r][c] = tree;

				//lay the tree based on its position in the grid and a slight deviation
				int x = c * cellSize + randInRange(-positionDeviation, positionDeviation);
				int y = r * cellSize + randInRange(-positionDeviation, positionDeviation);
				tree->translate(x, 0, y);

				//scale the tree
				float sizeScale = randInDoubleRange(treeSizeScaleMin, treeSizeScaleMax);
				float heightScale = randInDoubleRange(treeHeightScaleMin, treeHeightScaleMax);
				tree->scale(sizeScale, heightScale, sizeScale); //trees will be cylindrical

				//rotate the tree around y axis
				float angleDegrees = randInDoubleRange(0, 360);
				tree->rotateDegrees(angleDegrees, 0, 1, 0);

			}
		}
	}

	RenderableModel* item = new RenderableModel(treeModel, phong, true);
	float sizeScale = treeSizeScaleMin + (treeSizeScaleMax - treeSizeScaleMin) / 2.f;
	float heightScale = treeHeightScaleMin + (treeHeightScaleMax - treeHeightScaleMin) / 2.f;
	item->scale(sizeScale, heightScale, sizeScale);

	setControls(new DefaultControls(getPlayerView(), item));
}

void ForestScene::update(double dt)
{
	SceneWithPlayerView::update(dt);

	//move the spotlight in circular motion ("hardcoded")
	float angularVel = 1.6;
	TransformationMatrix matrix;
	matrix.translate(movingSpotlightAnchor);
	matrix.rotate(angularVel * dt, 0, 1, 0);
	matrix.translate(-movingSpotlightAnchor);
	movingSpotlight->setPos(matrix.applyTo(movingSpotlight->getPos()));


	//flashlight->setPos(camera->getPos());
	//flashlight->setDir(camera->getTarget());
}
