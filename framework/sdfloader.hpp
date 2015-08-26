#ifndef BUW_SDFLOADER_HPP
#define BUW_SDFLOADER_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "scene.hpp"
#include "material.hpp"

class Sdfloader
{
public:
      Sdfloader();
      Sdfloader(std::string file);
      ~Sdfloader();

      std::shared_ptr<Scene> loadscene(std::string file) const;
      std::string get_file() const;

private:
      std::string file_;
};

#endif
