#pragma once
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct AdvancedVertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 uv;

    AdvancedVertex() : pos(0), normal(0), uv(0) {

    }
};
