#ifndef BUW_LIGHTS_HPP
#define BUW_LIGHTS_HPP
#include <glm/vec3.hpp>
#include <string>
#include <iostream>
#include "color.hpp"

class Light
{
public:
    Light();
    Light(std::string const& n, glm::vec3 const& pos, glm::vec3 const& dl);

    // glm::vec3 const& pos() const;
    // glm::vec3 const& dl() const;

    // friend std::ostream& operator<<(std::ostream& os, Light const& l);

private:
    std::string name_;
    glm::vec3 pos_;
    glm::vec3 dlight_;
};

#endif //#define BUW_LIGHTS_HPP
