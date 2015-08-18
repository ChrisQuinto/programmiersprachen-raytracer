#ifndef BUW_SDFLOADER_HPP
#define BUW_SDFLOADER_HPP
#include <iostream>
#include <string>
#include "scene.hpp"
#include <fstream>
#include "material.hpp"
#include <map>

class Sdfloader
  {
    public:

      Sdfloader();
      Sdfloader(std::string file);
      ~Sdfloader();

      Scene loadscene(std::string file) const;
      std::string get_file() const;

    private:
      std::string file_;
  };

#endif
