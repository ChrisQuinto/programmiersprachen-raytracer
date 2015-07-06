#include "box.hpp"

Box::Box() :
    Box::Shape(),
    min_{0.0,0.0,0.0},
    max_{0.0,0.0,0.0} {}

Box::Box(glm::vec3 const& minimum, glm::vec3 const& maximum) :
    Box::Shape(),
    min_{minimum},
    max_{maximum} {}

Box::Box(glm::vec3 const& minimum, glm::vec3 const& maximum, std::string n, Color const& c) :
    Box::Shape(n,c),
    min_{minimum},
    max_{maximum} {}

glm::vec3 const& Box::min() const {
    return min_;
}

glm::vec3 const& Box::max() const {
    return max_;
}

float Box::width() const {
    return abs(max_.x - min_.x);
}

float Box::length() const {
    return abs(max_.y - min_.y);
}

float Box::hight() const {
    return abs(max_.z - min_.z);
}

/* virtual */ float Box::area() const {
    return ((2 * (width() * length())) + (2 * (width() * hight())) + (2 * (length() * hight())));
}

/* virtual */ float Box::volume() const {
    return (width() * length() * hight());
}

/* virtual */ std::ostream& Box::print(std::ostream& os) const {
    Shape::print(os);
    os << "Minimum: (" << min().x << "," << min().y << "," << min().z << ") \n";
    os << "Maximum: (" << max().x << "," << max().y << "," << max().z << ") \n";
    os << "Flaecheninhalt: " << area() << "\n";
    os << "Volumen: " << volume() << "\n \n";
    return os;
}
