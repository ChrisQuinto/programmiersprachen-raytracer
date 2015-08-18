#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP
#include <glm/vec3.hpp>
#include <string>
#include <iostream>

class Camera
{
public:
    Camera();
    Camera(std::string const& n, glm::vec3 const& pos, double const& fovx, int const& w, int const& h);
    std::string const& name() const;
    glm::vec3 const& pos() const;
    double const& fovx() const;
    int const& width() const;
    int const& heigth() const;

private:
    std::string name_;
    glm::vec3 pos_;
    double fovx_;
};


#endif
