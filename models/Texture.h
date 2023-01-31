#pragma once
#include <string>
#include <map>
#include "TextureType.h"
#include "ShaderProgram.h"
#include "CubeMapFilenames.h"

//this time using static members/methods instead of a Manager class
class Texture {
private:
	static std::map<std::string, Texture*>  loadedTextures;
	static int nextTextureUnit;
	int textureUnit;
	GLuint id;
	int numberOfComponents; //2 for 2D map, 3 for cube map
	const char* name;

	Texture(const char* name);
	void load(std::string filename, TextureType type);
	void load(CubeMapFilenames cubeMapFilenames, TextureType type);

public:
	static Texture* getTexture(std::string filename, const char* name = "material.diffuseTexUnit", TextureType type = TT_RGBA );
	static Texture* getCubeMapTexture(CubeMapFilenames cubeMapFilenames, const char* name = "material.diffuseTexUnit", TextureType type = TT_RGB);
	static void deleteTextures();

	void prep(ShaderProgram* shaderProgram);
	int getNumberOfComponents();

};