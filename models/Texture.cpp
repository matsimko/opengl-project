#include "Texture.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <stdexcept>

int Texture::nextTextureUnit = 0;
std::map<std::string, Texture*> Texture::loadedTextures; //the static variable needs to be defined even if not specifying any value!



Texture::Texture(const char* name)
{
    this->textureUnit = nextTextureUnit;
    nextTextureUnit++;
    this->id = 0;
    this->numberOfComponents = 0;

    this->name = name;
}

void Texture::load(std::string filename, TextureType type)
{
    this->numberOfComponents = 2;
    //GL_TEXTUREx seems to be a value that increments by one with higher numbers. Otherwise I wouldn't need to make a map from unit to gl_textureX.
    glActiveTexture(GL_TEXTURE0 + textureUnit);

    id = SOIL_load_OGL_texture(filename.c_str(), type, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (id == 0) {
        throw std::invalid_argument("Couldn't load a texture from the given filename.");
    }
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Texture::load(CubeMapFilenames cubeMapFilenames, TextureType type)
{
    this->numberOfComponents = 3;
    glActiveTexture(GL_TEXTURE0 + textureUnit);

    id = SOIL_load_OGL_cubemap
    (
        cubeMapFilenames.xpos.c_str(),
        cubeMapFilenames.xneg.c_str(),
        cubeMapFilenames.ypos.c_str(),
        cubeMapFilenames.yneg.c_str(),
        cubeMapFilenames.zpos.c_str(),
        cubeMapFilenames.zneg.c_str(),
        type,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS
    );
    if (id == 0) {
        throw std::invalid_argument("Couldn't load a cubemap from the given filenames.");
    }
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    //linear filtering
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //basically hide the borders of the cube
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

Texture* Texture::getTexture(std::string filename, const char* name, TextureType type)
{
    if (loadedTextures.find(filename) == loadedTextures.end()) {
        Texture* texture = new Texture(name);
        texture->load(filename, type);
        loadedTextures.insert({ filename, texture });
        return texture;
    }

    return loadedTextures.at(filename);
}

Texture* Texture::getCubeMapTexture(CubeMapFilenames cubeMapFilenames, const char* name, TextureType type)
{
    //the cubemap is cached by its xpos filename
    if (loadedTextures.find(cubeMapFilenames.xpos) == loadedTextures.end()) {
        Texture* texture = new Texture(name);
        texture->load(cubeMapFilenames, type);
        loadedTextures.insert({ cubeMapFilenames.xpos, texture });
        return texture;
    }

    return loadedTextures.at(cubeMapFilenames.xpos);
}

void Texture::deleteTextures()
{
    for (auto const& x : loadedTextures)
    {
        delete x.second;
    }
}

void Texture::prep(ShaderProgram* shaderProgram)
{
    shaderProgram->setUniformVariable(name, textureUnit);
}

int Texture::getNumberOfComponents()
{
    return numberOfComponents;
}

