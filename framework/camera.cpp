#include "camera.hpp"

CAMERA::CAMERA() :
    name_{"defaultcam"},
    pos_{0.0,0.0,0.0},
    fovx_{60.0},
    width_{640},
    heigth_{480} {}

Camera::Camera(std::string const& n, glm::vec3 const& pos, double const& fovx, int const& w, int const& h) :
    name_{n},
    pos_{pos},
    fovx_{fovx},
    width_{w},
    heigth_{h} {}

std::string const& Camera::name() const {
    return name_;
}
glm::vec3 const& Camera::pos() const {
    return pos_;
}
double const& Camera::fovx() const {
    return fovx_;
}
int const& Camera::width() const {
    return width_;
}
int const& Camera::heigth() const {
    return height_;
}
