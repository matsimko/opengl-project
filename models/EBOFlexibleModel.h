#pragma once
#include "VectorFlexibleModel.h"
#include <vector>

class EBOFlexibleModel :
    public VectorFlexibleModel
{
private:
    std::vector<GLuint> indices;

    void init(std::vector<GLuint> indices);
protected:
    // Inherited via Model
    virtual void doLoad(GLuint VBO) override;

    virtual void doDraw(ShaderProgram* shaderProgram) override;

public:
    EBOFlexibleModel(std::vector<GLfloat> vertices, std::vector<GLuint> indices, std::vector<int> attrFloatCounts, GLuint mode = GL_TRIANGLES);
    EBOFlexibleModel(std::vector<GLfloat> vertices, std::vector<GLuint> indices, std::vector<int> attrFloatCounts, Texture* texture, GLuint mode = GL_TRIANGLES);
    EBOFlexibleModel(std::vector<GLfloat> vertices, std::vector<GLuint> indices, std::vector<int> attrFloatCounts, Material* material, GLuint mode = GL_TRIANGLES);
    ~EBOFlexibleModel();

};

