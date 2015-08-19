#include "lights.hpp"

Light::Light() :
    name_{"noname"},
    pos_{0.0,0.0,0.0},
    dlight_{0.0,0.0,0.0} {}

Light::Light(std::string const& n, glm::vec3 const& pos, Color const& dl) :
    name_{n},
    pos_{pos},
    dlight_{dl} {}

std::string const& Light::name() const{
    return name_;
}

glm::vec3 const& Light::pos() const{
    return pos_;
}
Color const& Light::dl() const{
    return dlight_;
}

/*std::ostream& operator<<(std::ostream& os, Light const& l)
  {
    os << "(" << l.name_ << "," << l.pos() << "," << l.dl() <<")\n";
    return os;
  }*/
