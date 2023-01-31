#include "ModelManager.h"
#include <stdexcept>
#include "EBOFlexibleModel.h"

std::vector<int> ModelManager::posNormalUvTangentFloatCounts = { 3, 3, 2, 3 };
std::vector<int> ModelManager::posNormalUvFloatCounts = { 3, 3, 2 };

Material* ModelManager::loadMaterial(const aiScene* scene, aiMesh* mesh, std::string directory)
{
    Texture* texture = nullptr;
    //using just the first material of the mesh (and taking a diffuse texture)
    aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
    aiString str;
    if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
        mat->GetTexture(aiTextureType_DIFFUSE, 0, &str);
        std::string filename = directory + '/' + str.C_Str(); //expecting the texture to be in the same directory as the .obj
        texture = Texture::getTexture(filename);
    }
   
    //the default values are used if asiGetMaterial doesn't contain the particular key
    aiColor4D c(1.f, 1.f, 1.f, 1.f);
    aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT, &c);
    glm::vec4 ambient = glm::vec4(c.r, c.g, c.b, c.a);

    c = aiColor4D(1.f, 1.f, 1.f, 1.f);
    aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &c);
    glm::vec4 diffuse = glm::vec4(c.r, c.g, c.b, c.a);

    c = aiColor4D(1.f, 1.f, 1.f, 1.f);
    aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &c);
    glm::vec4 specular = glm::vec4(c.r, c.g, c.b, c.a);

    float shininess = 32;
    aiGetMaterialFloat(mat, AI_MATKEY_SHININESS, &shininess);

    return new Material(texture, ambient, diffuse, specular, shininess);
}

std::vector<GLfloat> ModelManager::loadVertices(aiMesh* mesh, bool useTangents)
{
    std::vector<GLfloat> vertices;

    if (mesh->mNumVertices <= 0) {
        return vertices;
    }

    //I want to scale the x and z to <-1, 1>, y to <0, 2> (so that the obj stands on the surface (y is height)).
    //This ways the size of all models will be relative to each other.
    //Only the coordinate with largest range will be mapped directly, the rest will be mapped relatively to that range.
    float minX, maxX;
    float minY, maxY;
    float minZ, maxZ;

    minX = maxX = mesh->mVertices[0].x;
    minY = maxY = mesh->mVertices[0].y;
    minZ = maxZ = mesh->mVertices[0].z;
    for (int i = 1; i < mesh->mNumVertices; i++) {
        minX = std::min(mesh->mVertices[i].x, minX);
        minY = std::min(mesh->mVertices[i].y, minY);
        minZ = std::min(mesh->mVertices[i].z, minZ);

        maxX = std::max(mesh->mVertices[i].x, maxX);
        maxY = std::max(mesh->mVertices[i].y, maxY);
        maxZ = std::max(mesh->mVertices[i].z, maxZ);
    }

    float rangeX = (maxX - minX);
    float rangeY = (maxY - minY);
    float rangeZ = (maxZ - minZ);
    float maxRange = std::max({ rangeX, rangeY, rangeZ });

    for (int i = 0; i < mesh->mNumVertices; i++)
    {
        //vertex.pos = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

        GLfloat posX = rangeX ? (-1.f + 2.f * (mesh->mVertices[i].x - minX) / rangeX) * (rangeX / maxRange) : 0;
        GLfloat posY = rangeY ? (0 + 2.f * (mesh->mVertices[i].y - minY) / rangeY) * (rangeY / maxRange) : 0;
        GLfloat posZ = rangeZ ? (-1.f + 2.f * (mesh->mVertices[i].z - minZ) / rangeZ) * (rangeZ / maxRange) : 0;
        vertices.push_back(posX);
        vertices.push_back(posY);
        vertices.push_back(posZ);

        if (mesh->HasNormals())
        {
            vertices.push_back(mesh->mNormals[i].x);
            vertices.push_back(mesh->mNormals[i].y);
            vertices.push_back(mesh->mNormals[i].z);
        }

        if (mesh->HasTextureCoords(0))
        {
            //uv coordinates
            vertices.push_back(mesh->mTextureCoords[0][i].x);
            vertices.push_back(mesh->mTextureCoords[0][i].y);

            //tangent
            if (useTangents) {
                vertices.push_back(mesh->mTangents[i].x);
                vertices.push_back(mesh->mTangents[i].y);
                vertices.push_back(mesh->mTangents[i].z);
            }
            
                
            //vertex.bitangent = glm::vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
        }
    }

    return vertices;
}

std::vector<GLuint> ModelManager::loadIndices(aiMesh* mesh)
{
  std::vector<GLuint> indices;
  for (int i = 0; i < mesh->mNumFaces; i++)
  {
      aiFace face = mesh->mFaces[i];
      for (int j = 0; j < face.mNumIndices; j++) //j=3 everytime though
          indices.push_back(face.mIndices[j]);
  };
  return indices;
}

const aiScene* ModelManager::loadScene(Assimp::Importer& import, std::string path)
{
    unsigned int importOptions = aiProcess_Triangulate
        | aiProcess_OptimizeMeshes              // slouèení malých plošek
        | aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodnì duplikuje
        | aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
        | aiProcess_CalcTangentSpace            // vypocet tangenty, nutny pro spravne pouziti normalove mapy
        | aiProcess_GenNormals;
    //| aiProcess_FlipUVs; //I flip the diffuse map in SOIL_load already, so no need to flip UV
    const aiScene* scene = import.ReadFile(path, importOptions);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        throw std::runtime_error(std::string("Errow while reading AdvancedModel from file: ") + import.GetErrorString());
    }

    return scene;
}

Model* ModelManager::loadModel(std::string path)
{
    //the importer owns the scene so it can't be created locally in the loadScene function...
    Assimp::Importer import;
    const aiScene* scene = loadScene(import, path);

    //using just the first mesh... (not even checking if it exists for now)
    aiMesh* mesh = scene->mMeshes[0];
    std::string directory = path.substr(0, path.find_last_of('/'));

    std::vector<GLfloat> vertices = loadVertices(mesh, false);
    std::vector<GLuint> indices = loadIndices(mesh);
    Material* material = loadMaterial(scene, mesh, directory);

    Model* model = new EBOFlexibleModel(vertices, indices, posNormalUvFloatCounts, material);
    model->load();
    return model;
}

Model* ModelManager::loadModel(std::string objPath, std::string diffuseTexPath, std::string normalMapPath)
{
    Assimp::Importer import;
    const aiScene* scene = loadScene(import, objPath);

    //using just the first mesh... (not even checking if it exists for now)
    aiMesh* mesh = scene->mMeshes[0];

    std::vector<GLfloat> vertices = loadVertices(mesh, true);
    std::vector<GLuint> indices = loadIndices(mesh);

    Texture* texture = Texture::getTexture(diffuseTexPath);
    Material* material = nullptr;
    if (!normalMapPath.empty()) {
        Texture* normalMap = Texture::getTexture(normalMapPath, "material.normalTexUnit");
        material = new Material(texture, normalMap);
    }
    else {
        material = new Material(texture);
    }
    

    Model* model = new EBOFlexibleModel(vertices, indices, posNormalUvTangentFloatCounts, material);
    model->load();
    return model;
}

