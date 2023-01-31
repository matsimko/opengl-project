#pragma once
#include "Model.h"
#include "Texture.h"
#include <vector>

//interprets the vertices depending on attrFloatCounts
//As of now I have subclasses which just define and pass the attrFloatCounts,
//so static methods here or having methods in ModelLoader might be a better idea
//(which would also free me from having to call load() in scenes)
class FlexibleModel : public Model {
public:

private:
	float* vertices;
	int verticesCount;
	GLenum mode;
	std::vector<int> attrFloatCounts;
	int vertexFloatCount;

	void init(const float* vertices, int verticesCount, std::vector<int> attrFloatCounts, GLuint mode);

public:
	FlexibleModel(const float* vertices, int verticesCount, std::vector<int> attrFloatCounts, GLuint mode = GL_TRIANGLES);
	FlexibleModel(const float* vertices, int verticesCount, std::vector<int> attrFloatCounts, Texture* texture, GLuint mode = GL_TRIANGLES);
	FlexibleModel(const float* vertices, int verticesCount, std::vector<int> attrFloatCounts, Material* material, GLuint mode = GL_TRIANGLES);
	~FlexibleModel();

	// Inherited via Model
	virtual void doLoad(GLuint VBO) override;
	virtual void doDraw(ShaderProgram* shaderProgram) override;
};
