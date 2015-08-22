#ifndef BUW_HIT_HPP
#define BUW_HIT_HPP
#include <glm/vec3.hpp>
#include <memory>
#include "ray.hpp"

class Shape;

struct Hit {
    Hit();
    Hit(bool hit, float dis, glm::vec3 const& intersection, glm::vec3 const& norm, std::shared_ptr<Shape> sptr);

    Hit& operator=(Hit const& hit);

    friend std::ostream& operator<<(std::ostream& os, Hit const& hit);

    bool hit_;
    float distance_;
    glm::vec3 intersection_;
    glm::vec3 normal_; //Normalenvektor am Schnittpunkt
    std::shared_ptr<Shape> sptr_;
};

#endif
