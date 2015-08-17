#ifndef BUW_COMPOSITE_HPP
#define BUW_COMPOSITE_HPP
#include "shape.hpp"

class Composite : public Shape
{
public:
    Composite();

    /* virtual */ float area() const override;

    /* virtual */ float volume() const override;

    /* virtual */ std::ostream& print(std::ostream& os) const override;

};

#endif
