#include "box.hpp"

Box::Box() :
    Box::Shape(),
    min_{0.0,0.0,0.0},
    max_{0.0,0.0,0.0} {
        // std::cout << "Default-Konstruktor-Aufruf fuer Box: " << name() << "\n";
    }

Box::Box(glm::vec3 const& minimum, glm::vec3 const& maximum) :
    Box::Shape(),
    min_{minimum},
    max_{maximum} {
        // std::cout << "Konstruktor-Aufruf fuer Box: " << name() << "\n";
    }

Box::Box(glm::vec3 const& minimum, glm::vec3 const& maximum, std::string n, Material const& m) :
    Box::Shape(n,m),
    min_{minimum},
    max_{maximum} {
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

/* virtual */ std::ostream& Box::print(std::ostream& os) const {
    os << "Box: \n";
    Shape::print(os);
    os << "Minimum: (" << min().x << "," << min().y << "," << min().z << ") \n";
    os << "Maximum: (" << max().x << "," << max().y << "," << max().z << ") \n";
    os << "Flaecheninhalt: " << area() << "\n";
    os << "Volumen: " << volume() << "\n\n";
    return os;
}

bool Box::intersect(Ray const& ray, float& distance) const {

    //glm::vec3 d = glm::normalize(ray.direction_);

    float t1 = 0;
    float t2 = 0;
    float t3 = 0;
    float t4 = 0;
    float t5 = 0;
    float t6 = 0;

    if (ray.direction_.x != 0)  //Schnittpunkte mit der x-Ebene
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
    }

    float inp = std::max(       //Eintrittspunkt
                    std::max( std::min(t1,t2), std::min(t3,t4) ),
                    std::min(t5,t6)
                    );

    float outp = std::min(      //Austrittspunkt
                    std::min( std::max(t1,t2), std::max(t3,t4) ),
                    std::max(t5,t6)
                    );

    if (outp < std::max(0.0f, inp))
    {
        return false;
    }

    //  distance = std::sqrt( ((ray.origin_.x * ray.origin_.x) + (ray.origin_.y * ray.origin_.y) + (ray.origin_.z * ray.origin_.z)) - () )
/*    distance = std::sqrt(
        (ray.direction_.x * (outp - inp) * ray.direction_.x * (outp - inp)) +
        (ray.direction_.y * (outp - inp) * ray.direction_.y * (outp - inp)) +
        (ray.direction_.z * (outp - inp) * ray.direction_.z * (outp - inp))
        );*/

    return true;

}
