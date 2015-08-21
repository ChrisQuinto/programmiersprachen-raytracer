#ifndef BUW_HIT_HPP
#define BUW_HIT_HPP
#include <glm/vec3.hpp>
#include <memory>
#include "ray.hpp"
#include "shape.hpp"

class Shape;

struct Hit {
    bool hit;
    float distance;
    glm::vec3 pos;
    glm::vec3 nvec;
    std::shared_ptr<Shape> shape;
};

#endif
