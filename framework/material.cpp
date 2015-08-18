#include "material.hpp"

Material::Material() :
    name_{"noname"},
    ka_{Color()},
    kd_{Color()},
    ks_{Color()},
    reflection_{0} {}

Material::Material(std::string const& n, Color const& a, Color const& d, Color const& s, float const& m) :
    name_{n},
    ka_{a},
    kd_{d},
    ks_{s},
    reflection_{m} {}

Material::Material(std::string const& n, Color const& a, float const& m) :
    name_{n},
    ka_{a},
    kd_{a},
    ks_{a},
    reflection_{m} {}

Material::~Material() {}

std::string const& Material::name() const{
    return name_;
}
Color const& Material::ka() const{
    return ka_;
}
Color const& Material::kd() const{
    return kd_;
}
Color const& Material::ks() const{
    return ks_;
}
float const& Material::m() const{
    return reflection_;
}

std::ostream& operator<<(std::ostream& os, Material const& m)
  {
    os << "(" << m.name_ << "," << m.ka() << "," << m.kd() << "," << m.ks() << "," << m.m() <<")\n";
    return os;
  }
