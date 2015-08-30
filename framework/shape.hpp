#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <cmath>
#include <string>
#include <iostream>
#include "ray.hpp"
#include "hit.hpp"
#include "material.hpp"

class Box;

class Shape
{
public:
    virtual ~Shape();

    std::string const& name() const;

    Material const& material() const;

    virtual float area() const = 0;

    virtual float volume() const = 0;

    virtual Hit intersect(Ray const& ray) = 0;

    virtual void translate(glm::vec3 const& move) = 0;

    virtual std::ostream& print(std::ostream& os) const;

protected:
    Shape();

    Shape(std::string const& n, Material const& m);

private:
    std::string name_;
    Material material_;
    glm::mat4x4 matrix_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s); //not a member function

#endif
