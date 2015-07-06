#ifndef RAY_BUW_HPP
#define RAY_BUW_HPP
#include <glm/vec3.hpp>

struct Ray
{
    Ray() :
    origin_{0.0,0.0,0.0},
    direction_{0.0,0.0,0.0} {}

    Ray(glm::vec3 const& o, glm::vec3 const& d) :
    origin_{o},
    direction_{d} {}

    glm::vec3 origin_;
    glm::vec3 direction_;
};

#endif
