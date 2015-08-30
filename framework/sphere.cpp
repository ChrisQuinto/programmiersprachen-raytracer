#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/gtx/intersect.hpp>
#include "sphere.hpp"

Sphere::Sphere() :
    Sphere::Shape(),
    center_{glm::vec3{0.0,0.0,0.0}},
    radius_{0.0} {
        // std::cout << "Default-Konstruktor-Aufruf fuer Sphere: " << name() << "\n";
    }

Sphere::Sphere(glm::vec3 const& vec, float r) :
    Sphere::Shape(),
    center_{vec},
    radius_{r} {
        // std::cout << "Konstruktor-Aufruf fuer Sphere: " << name() << "\n";
    }

Sphere::Sphere(glm::vec3 const& vec, float r, std::string const& n, Material const& m) :
    Sphere::Shape(n,m),
    center_{vec},
    radius_{r} {
        // std::cout << "Konstruktor-Aufruf fuer Sphere: " << name() << "\n";
    }

Sphere::~Sphere() {
        // std::cout << "Destruktor-Aufruf fuer Sphere: " << name() << "\n";
    }

glm::vec3 const& Sphere::center() const {
        return center_;
    }

float Sphere::radius() const {
        return radius_;
    }

/* virtual */ float Sphere::area() const {
        return 4.0f * M_PI * radius_ * radius_;
    }

/* virtual */ float Sphere::volume() const {
        return (4.0f/3.0f) * M_PI * (radius_ * radius_ * radius_);
    }

/* virtual */ Hit Sphere::intersect(Ray const& ray) {
    Hit s_hit;

    s_hit.hit_ = glm::intersectRaySphere(
        ray.origin_,
        glm::normalize(ray.direction_),
        center_, radius_,
        s_hit.intersection_, s_hit.normal_
    );

    s_hit.distance_ = glm::distance(ray.origin_, s_hit.intersection_);

    s_hit.sptr_ = std::make_shared<Sphere>(*this);

    return s_hit;
}

void Sphere::setcenter(glm::vec3 const& newcenter) {
    center_ = newcenter;
}

void Sphere::translate(glm::vec3 const& move) {
    center_ = newcenter;
}

/* virtual */ std::ostream& Sphere::print(std::ostream& os) const {
    os << "Sphere: \n";
    Shape::print(os); //Erweiterung
    os << "Mittelpunkt: (" << center().x << "," << center().y << "," << center().z << ") \n";
    os << "Radius: " << radius() << "\n";
    os << "Flaecheninhalt: " << area() << "\n";
    os << "Volumen: " << volume() << "\n\n";
    return os;
}

/*bool Sphere::intersect(Ray const& ray, float& distance) const {
    return glm::intersectRaySphere(ray.origin_, glm::normalize(ray.direction_), center_, radius_ * radius_, distance);
}*/
