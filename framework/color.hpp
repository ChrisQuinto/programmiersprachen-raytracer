// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>

struct Color
{
    Color() :
    r{0.0},
    g{0.0},
    b{0.0} {}

    Color(float red, float green, float blue) :
    r{red},
    g{green},
    b{blue} {}

    ~Color() {}

    float r;
    float g;
    float b;

    friend std::ostream& operator<<(std::ostream& os, Color const& c)
    {
      os << "(" << c.r << "," << c.g << "," << c.b << ")\n";
      return os;
    }

    bool operator==(Color const& other) const
    {
      return ((r == other.r) && (g == other.g) && (b == other.b));
    }

    bool operator!=(Color const& other) const
    {
        return !(*this == other);
    }

    Color& operator+=(Color const& other)
    {
      r += other.r;
      g += other.g;
      b += other.b;
      return *this;
    }

    Color& operator-=(Color const& other)
    {
      r -= other.r;
      g -= other.g;
      b -= other.b;
      return *this;
    }

    friend Color operator+(Color const& a, Color const& b)
    {
      auto tmp(a);
      tmp += b;
      return tmp;
    }

    friend Color operator-(Color const& a, Color const& b)
    {
      auto tmp(a);
      tmp -= b;
      return tmp;
    }

    Color& operator=(Color const& other)
    {
      r = other.r;
      g = other.g;
      b = other.b;
      return *this;
    }

    Color& operator*(Color const& other)
    {
      r *= other.r;
      g *= other.g;
      b *= other.b;
      return *this;
    }

    Color operator*(float const& x)
    {
      r = r * x;
      g = r * x;
      b = r * x;
      return *this;
    }

        Color operator/(float const& x)
    {
      r /= x;
      g /= x;
      b /= x;
      return *this;
    }


};

#endif
