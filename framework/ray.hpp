#ifndef RAY_BUW_HPP
#define RAY_BUW_HPP
#include <glm/vec3.hpp>
#include <iostream>
#include <string>

struct Ray
{
    Ray() :
    origin_{0.0,0.0,0.0},
    direction_{0.0,0.0,0.0},
    inv_direction_{-0.0,-0.0,-0.0} {}

    Ray(glm::vec3 const& o, glm::vec3 const& d) :
    origin_{o},
    direction_{d},
    inv_direction_{1.0/d.x,1.0/d.y,1.0/d.z} {}

    ~Ray() {}

    friend std::ostream& operator<<(std::ostream& os, Ray const& ray) {
        os << "Origin: ("
            << ray.origin_.x << ","
            << ray.origin_.y << ","
            << ray.origin_.z << ") \n"
            << "Direction: ("
            << ray.direction_.x << ","
            << ray.direction_.y << ","
            << ray.direction_.z << ") \n";
        return os;
    }

    glm::vec3 origin_;
    glm::vec3 direction_;
    glm::vec3 inv_direction_;
};

#endif
