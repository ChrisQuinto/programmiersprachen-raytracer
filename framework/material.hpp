#ifndef BUW_MATERIAL_HPP
#define BUW_MATERIAL_HPP
#include <string>
#include "color.hpp"

class Material
{
public:
    Material();
    Material(std::string const& n, Color const& a, Color const& d, Color const& s, float const& m);
    Material(std::string const& n, Color const& a, float const& m);
    ~Material();

    std::string const& name() const;
    Color const& ka() const;
    Color const& kd() const;
    Color const& ks() const;
    float const& m() const;

    friend std::ostream& operator<<(std::ostream& os, Material const& m);

    bool operator==(Material const& m2) const{
      return ((ka() == m2.ka()) && (kd() == m2.kd()) && (ks() == m2.ks()));
    }

private:
    std::string name_;
    Color ka_;
    Color kd_;
    Color ks_;
    float reflection_;
};

#endif
