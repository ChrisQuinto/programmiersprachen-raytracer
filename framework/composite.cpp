#include "composite.hpp"

Composite::Composite() :
    Composite::Shape() {}

/* virtual */ float Composite::area() const {
        return 0;
    }

/* virtual */ float Composite::volume() const {
        return 0;
    }

/* virtual */ std::ostream& Composite::print(std::ostream& os) const {
    Shape::print(os); //Erweiterung
    return os;
}
