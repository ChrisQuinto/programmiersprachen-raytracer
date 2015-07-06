#ifndef SPHERE_BUW_HPP
#define SPHERE_BUW_HPP
#include "shape.hpp"
#include "ray.hpp"

class Sphere : public Shape
{
public:
    Sphere();

    Sphere(glm::vec3 const& vec, float r);

    Sphere(glm::vec3 const& vec, float r, std::string const& n, Color const& c);

    ~Sphere();

    glm::vec3 const& center() const;

    float radius() const;

    bool intersect(Ray const& ray, float& distance) const;

    /* virtual */ float area() const override;

    /* virtual */ float volume() const override;

    /* virtual */ std::ostream& print(std::ostream& os) const override;

private:
    glm::vec3 center_;
    float radius_;
};

#endif
