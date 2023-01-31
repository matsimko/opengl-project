#include "Crosshair.h"


const int VERTICES_SIZE = 36;

float vertices[] = {
	-0.2f, 1.f, 0.f,
	0.2f, 1.f, 0.f,
	-0.2f, -1.f, 0.f,

	0.2f, 1.f, 0.5f,
	-0.2f, -1.f, 0.5f,
	0.2f, -1.f, 0.5f,

	1.f, -0.2f, 0.f,
	1.f, 0.2f, 0.f,
	-1.f, -0.2f, 0.f,

	1.f, 0.2f, 0.f,
	-1.f, -0.2f, 0.f,
	-1.f, 0.2f, 0.f,
};

void Crosshair::setUpVertices()
{
	float baseScale = 0.01f;
	float thickness = this->thickness * baseScale;
	float length = this->length * baseScale;

	//vertices forming the vertical rectangle
	for (int i = 0; i < VERTICES_SIZE / 2; i += 3) {
		vertices[i] *= thickness;
		vertices[i + 1] *= length;
	}
	//vertices forming the horizontal rectangle
	for (int i = VERTICES_SIZE / 2; i < VERTICES_SIZE; i += 3) {
		vertices[i] *= length;
		vertices[i + 1] *= thickness;
	}
}

Crosshair::Crosshair(glm::vec4 color, float length, float thickness)
{
	this->color = color;
	this->thickness = thickness;
	this->length = length;
	setUpVertices();

	Material* material = new Material();
	material->setDiffuse(color);
	model = new ModelWithPosition(vertices, VERTICES_SIZE, material);
	model->load();
}

void Crosshair::draw(ShaderProgram* shaderProgram)
{
	model->draw(shaderProgram);
}
