#ifndef RAY_BUW_HPP
#define RAY_BUW_HPP
#include <glm/vec3.hpp>

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

    glm::vec3 origin_;
    glm::vec3 direction_;
    glm::vec3 inv_direction_;
};

#endif
