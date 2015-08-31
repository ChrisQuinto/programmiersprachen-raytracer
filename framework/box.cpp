#include <limits>
#include "box.hpp"

Box::Box() :
    Box::Shape(),
    min_{0.0,0.0,0.0},
    max_{0.0,0.0,0.0} {
        // std::cout << "Default-Konstruktor-Aufruf fuer Box: " << name() << "\n";
    }

Box::Box(glm::vec3 const& minimum, glm::vec3 const& maximum) :
    Box::Shape(),
    min_{
        min_.x = std::min(minimum.x,maximum.x),
        min_.y = std::min(minimum.y,maximum.y),
        min_.z = std::min(minimum.z,maximum.z)
    },
    max_{
        max_.x = std::max(minimum.x,maximum.x),
        max_.y = std::max(minimum.y,maximum.y),
        max_.z = std::max(minimum.z,maximum.z)
    } {
        // std::cout << "Konstruktor-Aufruf fuer Box: " << name() << "\n";
    }

Box::Box(glm::vec3 const& minimum, glm::vec3 const& maximum, std::string n, Material const& m) :
    Box::Shape(n,m),
    min_{
        min_.x = std::min(minimum.x,maximum.x),
        min_.y = std::min(minimum.y,maximum.y),
        min_.z = std::min(minimum.z,maximum.z)
    },
    max_{
        max_.x = std::max(minimum.x,maximum.x),
        max_.y = std::max(minimum.y,maximum.y),
        max_.z = std::max(minimum.z,maximum.z)
    } {
        // std::cout << "Konstruktor-Aufruf fuer Box: " << name() << "\n";
    }

Box::~Box() {
        // std::cout << "Destruktor-Aufruf fuer Box: " << name() << "\n";
    }


glm::vec3 const& Box::min() const {
    return min_;
}

glm::vec3 const& Box::max() const {
    return max_;
}

/* virtual */ float Box::area() const {
    float width = abs(max_.x - min_.x);
    float length = abs(max_.y - min_.y);
    float height = abs(max_.z - min_.z);
    return (2 * width * length + 2 * width * height + 2 * length * height);
}

/* virtual */ float Box::volume() const {
    float width = abs(max_.x - min_.x);
    float length = abs(max_.y - min_.y);
    float height = abs(max_.z - min_.z);
    return (width * length * height);
}

/* virtual */ Hit Box::intersect(Ray const& ray) {

    float t1 = (max_.x - ray.origin_.x) * ray.inv_direction_.x;
    float t2 = (min_.x - ray.origin_.x) * ray.inv_direction_.x;
    float t3 = (max_.y - ray.origin_.y) * ray.inv_direction_.y;
    float t4 = (min_.y - ray.origin_.y) * ray.inv_direction_.y;
    float t5 = (max_.z - ray.origin_.z) * ray.inv_direction_.z;
    float t6 = (min_.z - ray.origin_.z) * ray.inv_direction_.z;

    //Range on x-Ebene for possible intersection
    float tmax = std::max(t1,t2);
    float tmin = std::min(t1,t2);
    //Range on y-Ebene for possible intersection after looking on x-Ebene
    tmax = std::min(std::max(t3,t4),tmax);
    tmin = std::max(std::min(t3,t4),tmin);
    //Range on z-Ebene for possible intersection after looking on x and y
    tmax = std::min(std::max(t5,t6),tmax);
    tmin = std::max(std::min(t5,t6),tmin);

    /*if (ray.direction_.x != 0)  //Schnittpunkte mit der x-Ebene
    {
        t1 = (std::min(min_.x - ray.origin_.x , max_.x - ray.origin_.x )) / ray.direction_.x;
        t2 = (std::max(min_.x - ray.origin_.x , max_.x - ray.origin_.x )) / ray.direction_.x;
    }

    if (ray.direction_.y != 0)  //Schnittpunkte mit der y-Ebene
    {
        t3 = (std::min(min_.y - ray.origin_.y , max_.y - ray.origin_.y )) / ray.direction_.y;
        t4 = (std::max(min_.y - ray.origin_.y , max_.y - ray.origin_.y )) / ray.direction_.y;
    }

    if (ray.direction_.z != 0)  //Schnittpunkte mit der x-Ebene
    {
        t5 = (std::min(min_.z - ray.origin_.z , max_.z - ray.origin_.z )) / ray.direction_.z;
        t6 = (std::max(min_.z - ray.origin_.z , max_.z - ray.origin_.z )) / ray.direction_.z;
    }*/

    Hit b_hit;

    if (tmax > std::max(0.0f, tmin)) {
        b_hit.distance_ = sqrt(tmin * tmin *
                             (ray.direction_.x * ray.direction_.x +
                              ray.direction_.y * ray.direction_.y +
                              ray.direction_.z * ray.direction_.z)
                            );

        b_hit.intersection_ = glm::vec3{
            tmin * ray.direction_.x,
            tmin * ray.direction_.y,
            tmin * ray.direction_.z
        };

        glm::vec3 normal{std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
        float bias = 0.0009;
        //getting the normal vec on the side of the intersection
        if (abs(b_hit.intersection_.x - max_.x) < bias) {
            normal = glm::vec3{1.0, 0.0, 0.0};
        } else if (abs(b_hit.intersection_.x - min_.x) < bias) {
            normal = glm::vec3{-1.0, 0.0, 0.0};
        } else if (abs(b_hit.intersection_.y - max_.y) < bias) {
            normal = glm::vec3{0.0, 1.0, 0.0};
        } else if (abs(b_hit.intersection_.y - min_.y) < bias) {
            normal = glm::vec3{0.0, -1.0, 0.0};
        } else if (abs(b_hit.intersection_.z - max_.z) < bias) {
            normal = glm::vec3{0.0, 0.0, 1.0};
        } else if (abs(b_hit.intersection_.z - min_.z) < bias) {
            normal = glm::vec3{0.0, 0.0, -1.0};
        }

        // std::cout << "INTERSECT IS GOING ON: \n";
        // std::cout << b_hit.intersection_.x << std::endl;
        // std::cout << max_.x << std::endl;
        // std::cout << min_.x << std::endl;
        // std::cout << b_hit.intersection_.y << std::endl;
        // std::cout << max_.y << std::endl;
        // std::cout << min_.y << std::endl;
        // std::cout << b_hit.intersection_.z << std::endl;
        // std::cout << max_.z << std::endl;
        // std::cout << min_.z << std::endl;

        b_hit.normal_ = normal;
        b_hit.sptr_ = std::make_shared<Box>(*this);
        b_hit.hit_ = true;
    }

    return b_hit;
}

/* virtual */ void Box::translate(glm::vec3 const& move) {
    //what to do? what to do?
}

/* virtual */ std::ostream& Box::print(std::ostream& os) const {
    os << "Box: \n";
    Shape::print(os);
    os << "Minimum: (" << min().x << "," << min().y << "," << min().z << ") \n";
    os << "Maximum: (" << max().x << "," << max().y << "," << max().z << ") \n";
    os << "Flaecheninhalt: " << area() << "\n";
    os << "Volumen: " << volume() << "\n\n";
    return os;
}
