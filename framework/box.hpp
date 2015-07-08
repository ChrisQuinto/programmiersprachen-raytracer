#ifndef BOX_BUW_HPP
#define BOX_BUW_HPP
#include <cmath>
#include <algorithm>
#include "shape.hpp"
#include "ray.hpp"
#include "material.hpp"

class Box : public Shape
{
public:
    Box();

    Box(glm::vec3 const& minimum, glm::vec3 const& maximum);

    Box(glm::vec3 const& minimum, glm::vec3 const& maximum, std::string n, Material const& m);

    glm::vec3 const& min() const;

    glm::vec3 const& max() const;

    float width() const;

    float length() const;

    float hight() const;

    bool intersect(Ray const& ray, float& distance) const;

    /* virtual */ float area() const override;

    /* virtual */ float volume() const override;

    /* virtual */ std::ostream& print(std::ostream& os) const override;

private:
    glm::vec3 min_;
    glm::vec3 max_;
};

#endif
