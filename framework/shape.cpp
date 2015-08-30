#include "shape.hpp"

Shape::Shape() :
    name_("defaultshape"),
    material_{Material{}},
    matrix_{glm::mat4x4{1,0,0,0,
                        0,1,0,0,
                        0,0,1,0,
                        0,0,0,1}} {
        // std::cout << "Default-Konstruktor-Aufruf fuer Shape: " << name() << "\n";
    }

Shape::Shape(std::string const& n, Material const& m) :
    name_(n),
    material_{m},
    matrix_{glm::mat4x4{1,0,0,0,
                        0,1,0,0,
                        0,0,1,0,
                        0,0,0,1}} {
        // std::cout << "Konstruktor-Aufruf fuer Shape: " << name() << "\n";
    }

Shape::~Shape() {
        // std::cout << "Destruktor-Aufruf fuer Shape: " << name() << "\n";
}

std::string const& Shape::name() const {
    return name_;
}

Material const& Shape::material() const {
    return material_;
}

std::ostream& Shape::print(std::ostream& os) const {
    os << "Name: " << name() << "\n";
    os << material();
    return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
    return s.print(os);
}
