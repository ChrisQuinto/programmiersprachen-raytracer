#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP
#include <glm/vec3.hpp>
#include <string>
#include <iostream>

class Camera
{
public:
    Camera();
    Camera(std::string const& n, float const& fovx);
    ~Camera();

    std::string const& name() const;
    glm::vec3 const& pos() const;
    float const& fovx() const;

    friend std::ostream& operator<<(std::ostream& os, Camera const& c);

private:
    std::string name_;
    glm::vec3 pos_;
    float fovx_;
};


#endif
