#pragma once
#include "Updatable.h"
#include <vector>
#include "RenderableModel.h"
#include <glm/vec3.hpp>

class BezierMover :
    public Updatable
{
private:
    std::vector<glm::vec3> points;
    RenderableModel* obj;
    float tParamPerSec;
    bool forward;

    float tParam;
    int n;
    int factorial(int n);
    int numberOfCombinations(int n, int k);
    float bernsteinPolynom(int i);
public:
    //tParamPerSec because it's not simple to figure out the length of the bezier curve
    BezierMover(std::vector<glm::vec3> points,RenderableModel* obj, float tParamPerSec = 0.2);

    // Inherited via Updatable
    virtual void update(double dt) override;
};

