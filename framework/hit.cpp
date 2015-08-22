#include "hit.hpp"
#include "shape.hpp"

Hit::Hit() :
hit_{false},
distance_{INFINITY},
intersection_{glm::vec3{ INFINITY,INFINITY,INFINITY }},
normal_{glm::vec3{ INFINITY,INFINITY,INFINITY }},
sptr_{nullptr} {}

Hit::Hit(bool hit, float dis, glm::vec3 const& intersection,
    glm::vec3 const& norm, std::shared_ptr<Shape> sptr) :
hit_{hit},
distance_{dis},
intersection_{intersection},
normal_{norm},
sptr_{sptr} {}

Hit& Hit::operator=(Hit const& hit) {
    if (this == &hit) {
        return *this;
    }

    hit_ = hit.hit_;
    distance_ = hit.distance_;
    intersection_ = hit.intersection_;
    normal_ = hit.normal_;
    sptr_ = hit.sptr_;

    return *this;
}

bool Hit::operator==(Hit const& hit2) const{
      return ((hit_ == hit2.hit_) && (distance_ == hit2.distance_) && (intersection_ == hit2.intersection_) && (normal_ == hit2.normal_) && (sptr_ == hit2.sptr_));
    }

std::ostream& operator<<(std::ostream& os, Hit const& hit) {
    os << "Hit: " << hit.hit_ << std::endl
       << "Distanz: " << hit.distance_ << std::endl
       << "Intersection: ("
       << hit.intersection_.x << ", "
       << hit.intersection_.y << ", "
       << hit.intersection_.z << ")" << std::endl
       << "Normal: ("
       << hit.normal_.x << ", "
       << hit.normal_.y << ", "
       << hit.normal_.z << ")" << std::endl;
    return os;
}
