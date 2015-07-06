#ifndef BOX_BUW_HPP
#define BOX_BUW_HPP
#include "shape.hpp"
#include "ray.hpp"

class Box : public Shape
{
public:
    Box();

    Box(glm::vec3 const& minimum, glm::vec3 const& maximum);

    Box(glm::vec3 const& minimum, glm::vec3 const& maximum, std::string n, Color const& c);

    glm::vec3 const& min() const;

    glm::vec3 const& max() const;

    float width() const;

    float length() const;

    float hight() const;

    /* virtual */ float area() const override;

    /* virtual */ float volume() const override;

    /* virtual */ std::ostream& print(std::ostream& os) const override;

private:
    glm::vec3 min_;
    glm::vec3 max_;
};

#endif
