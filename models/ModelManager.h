#pragma once
#include "Model.h"
#include <string>
#include "Material.h"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class ModelManager {
private:
	Material* loadMaterial(const aiScene* scene, aiMesh* mesh, std::string directory);
	std::vector<GLfloat>  loadVertices(aiMesh* mesh, bool useTangents);
	std::vector<GLuint> loadIndices(aiMesh* mesh);

	const aiScene* loadScene(Assimp::Importer& import, std::string path);

	static std::vector<int> posNormalUvTangentFloatCounts;
	static std::vector<int> posNormalUvFloatCounts;

public:
	//diffuse texture is expected to be in the same directory as the obj (the name is retrieved from .mtl file)
	Model* loadModel(std::string path);

	Model* loadModel(std::string objPath, std::string diffuseTexPath, std::string normalMapPath = "");
};
