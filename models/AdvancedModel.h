#pragma once
#include "Model.h"
#include <string>
#include "AdvancedVertex.h"
#include <vector>
#include "Material.h"

//This model could probably also load models without normal/uv (using bools hasUv, hasNormal and check for them during doLoad),
//but more data would be send to GPU than needed.
class AdvancedModel : public Model {
private:
	std::vector<AdvancedVertex> vertices;
	std::vector<GLuint> indices;


protected:
	virtual void doLoad(GLuint VBO) override;
	virtual void doDraw(ShaderProgram* shaderProgram) override;
public:
	AdvancedModel(std::vector<AdvancedVertex> vertices, std::vector<GLuint> indices, Material* material);

};
