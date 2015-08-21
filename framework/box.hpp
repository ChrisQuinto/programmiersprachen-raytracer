#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP
#include <algorithm>
#include "shape.hpp"

class Box : public Shape
{
public:
    Box();

    Box(glm::vec3 const& minimum, glm::vec3 const& maximum);

    Box(glm::vec3 const& minimum, glm::vec3 const& maximum, std::string n, Material const& m);

    ~Box();

    glm::vec3 const& min() const;

    glm::vec3 const& max() const;

    /* virtual */ float area() const override;

    /* virtual */ float volume() const override;

    /* virtual */ std::ostream& print(std::ostream& os) const override;

    bool intersect(Ray const& ray, float& distance) const;

private:
    glm::vec3 min_;
    glm::vec3 max_;
};

#endif
