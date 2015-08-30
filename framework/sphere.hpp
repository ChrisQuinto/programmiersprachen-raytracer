#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP
#include "shape.hpp"

class Sphere : public Shape
{
public:
    Sphere();

    Sphere(glm::vec3 const& vec, float r);

    Sphere(glm::vec3 const& vec, float r, std::string const& n, Material const& m);

    ~Sphere();

    glm::vec3 const& center() const;

    float radius() const;

    void translate(glm::vec3 const& newcenter);

    /* virtual */ float area() const override;

    /* virtual */ float volume() const override;

    /* virtual */ Hit intersect(Ray const& ray) override;

    /* virtual */ std::ostream& print(std::ostream& os) const override;

private:
    glm::vec3 center_;
    float radius_;
};

#endif
