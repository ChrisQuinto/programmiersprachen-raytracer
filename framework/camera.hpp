#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP
#include <string>
#include <iostream>
#include "color.hpp"

class Camera
{
public:
    Camera();
    Camera(std::string const& n, glm::vec3 const& pos, double const& fovx, int const& w, int const& h);
    std::string const& name() const;
    glm::vec3 const& pos() const;
    double const& fovx() const;
    int const& width() const;
    int const& height() const;

private:
    std::string name_;
    glm::vec3 pos_;
    double fovx_;
    int width_;
    int heigth_;
};


#endif
