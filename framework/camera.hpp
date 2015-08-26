#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP
#include <glm/vec3.hpp>
#include <string>
#include <iostream>
#include "ray.hpp"


struct Camera
{
    Camera();
    Camera(std::string const& n, int x, int y, double const& fovx);
    ~Camera();

    std::string const& name() const;
    glm::vec3 const& pos() const;
    int const& xres() const;
    int const& yres() const;
    double const& fovx() const;
    Ray const castray(glm::vec3 d);

    friend std::ostream& operator<<(std::ostream& os, Camera const& c);

    std::string name_;
    glm::vec3 pos_;
    int xres_;
    int yres_;
    double fovx_;
};


#endif
