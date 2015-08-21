#include "shape.hpp"

Shape::Shape() :
    name_("defaultshape"),
    material_{Material{}} {
        // std::cout << "Default-Konstruktor-Aufruf fuer: " << name() << "\n";
    }

Shape::Shape(std::string const& n, Material const& m) :
    name_(n),
    material_{m} {
        // std::cout << "Konstruktor-Aufruf fuer: " << name() << "\n";
    }

Shape::~Shape() {
        // std::cout << "Destruktor-Aufruf fuer: " << name() << "\n";
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
