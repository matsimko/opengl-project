#include "Skybox.h"
#include "App.h"
#include "ShaderManager.h"

Skybox::Skybox(const float * vertices, int verticesCount, CubeMapFilenames cubeMapFilenames)
{
	Texture *cubeMap = Texture::getCubeMapTexture(cubeMapFilenames);
	model = new ModelWithPosition(vertices, verticesCount, cubeMap);
	model->load();
	shaderProgram = App::getInstance().getShaderManager()->getShaderProgram(ShaderManager::SKYBOX);
}

void Skybox::render()
{
	glDepthMask(GL_FALSE); //turn off depth buffer so that it will be at the background no matter what
	shaderProgram->use();
	model->draw(shaderProgram);
	glDepthMask(GL_TRUE);
}


void Skybox::onViewMatrixChanged(Camera* camera)
{
	//Removing the translation component from the view matrix,
	//because the skybox should be at the origin no matter where the cam moves, but the skybox still wants to react to rotations of the cam
	glm::mat4 viewMatrix = glm::mat4(glm::mat3(camera->getViewMatrix()));
	shaderProgram->use();
	shaderProgram->setViewMatrix(viewMatrix);
	//the shader doesn't use camPos, so i don't need to try to update it
}

void Skybox::onProjectionMatrixChanged(Camera* camera)
{
	shaderProgram->onProjectionMatrixChanged(camera);
}

