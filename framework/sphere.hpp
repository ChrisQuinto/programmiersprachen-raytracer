#ifndef SPHERE_BUW_HPP
#define SPHERE_BUW_HPP
#include "shape.hpp"

const double PI = 3.141592653589793238463;

class Sphere : public Shape
{
public:
    Sphere() :
    center_{glm::vec3{0.0,0.0,0.0}},
    radius_{0.0} {}

    Sphere(glm::vec3 const& vec, double r) :
    center_{vec},
    radius_{r} {}

    glm::vec3 center() {
        return center_;
    }

    double radius() {
        return radius_;
    }

    /* virtual */ double area() const {

    }

    /* virtual */ double volume() const {
    return (4/3) * M_PI * (radius_ * radius_ * radius_);
    }

private:
    glm::vec3 center_;
    double radius_;
};

#endif
