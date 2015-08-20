#include "camera.hpp"

Camera::Camera() :
    name_{"defaultcam"},
    pos_{0.0,0.0,0.0},
    fovx_{60.0f} {}

Camera::Camera(std::string const& n, float const& fovx) :
    name_{n},
    pos_{0.0,0.0,0.0},
    fovx_{fovx} {}

Camera::~Camera() {}

std::string const& Camera::name() const {
    return name_;
}
glm::vec3 const& Camera::pos() const {
    return pos_;
}
float const& Camera::fovx() const {
    return fovx_;
}

std::ostream& operator<<(std::ostream& os, Camera const& c)
  {
    os << "Camera: \n"
       << "Name: " << c.name() << "\n"
       << "Pos: (" << c.pos().x << "," << c.pos().y << "," << c.pos().z << ")\n"
       << "Winkel: "<< c.fovx() << "\n\n";
    return os;
  }
