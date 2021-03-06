#include "camera.hpp"

Camera::Camera() :
    name_{"defaultcam"},
    pos_{0.0,0.0,0.0},
    xres_{500},
    yres_{500},
    fovx_{60.0f} {}

Camera::Camera(std::string const& n,int x,int y, double const& fovx) :
    name_{n},
    pos_{0.0,0.0,0.0},
    xres_{x},
    yres_{y},
    fovx_{fovx} {}

Camera::~Camera() {}

std::string const& Camera::name() const {
    return name_;
}
glm::vec3 const& Camera::pos() const {
    return pos_;
}
int const& Camera::xres() const {
    return xres_;
}
int const& Camera::yres() const {
    return yres_;
}
double const& Camera::fovx() const {
    return fovx_;
}

Ray const Camera::castray(glm::vec3 d) {
  Ray r1(pos_, d);
  return r1;
}

std::ostream& operator<<(std::ostream& os, Camera const& c)
  {
    os << "Camera: \n"
       << "Name: " << c.name() << "\n"
       << "Pos: (" << c.pos().x << "," << c.pos().y << "," << c.pos().z << ")\n"
       << "Aufloesung: " << c.xres() << "x" << c.yres() << "\n"
       << "Winkel: "<< c.fovx() << "\n\n";
    return os;
  }
