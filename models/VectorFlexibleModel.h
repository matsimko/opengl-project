#pragma once
#include "Model.h"
#include <vector>

class VectorFlexibleModel :
    public Model
{
private:
    int verticesCount;
    GLenum mode;
    std::vector<GLfloat> vertices;
    std::vector<int> attrFloatCounts;
    int vertexFloatCount;

    void init(std::vector<GLfloat> vertices, std::vector<int> attrFloatCounts, GLuint mode);
protected:
    // Inherited via Model
    virtual void doLoad(GLuint VBO) override;

    virtual void doDraw(ShaderProgram* shaderProgram) override;

public:
    VectorFlexibleModel(std::vector<GLfloat> vertices, std::vector<int> attrFloatCounts, GLuint mode = GL_TRIANGLES);
    VectorFlexibleModel(std::vector<GLfloat> vertices, std::vector<int> attrFloatCounts, Texture* texture, GLuint mode = GL_TRIANGLES);
    VectorFlexibleModel(std::vector<GLfloat> vertices, std::vector<int> attrFloatCounts, Material* material, GLuint mode = GL_TRIANGLES);
    ~VectorFlexibleModel();
};

