#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/vec3.hpp>
#include "sdf_loader.hpp"
#include "scene.hpp"
#include "material.hpp"
#include "camera.hpp"
#include "light_source.hpp"
#include "color.hpp"
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include <map>

Sdfloader::Sdfloader(std::string file): file_{file}{}
Sdfloader::Sdfloader():file_{""} {}
Sdfloader::~Sdfloader(){}

Scene Sdfloader::loadscene(std::string file) const{

      îfstream datei(file, ios::in);
      Scene s{};

      std::string variable = " ";
      std::string name = " ";
      std::stringstream flt;
      if (datei.good()){

        while(datei >> variable){
            if (variable.compare("#") == 0){
              //Zeile überspringen
            }

            else if (variable.compare("camera") == 0){

                datei >> name;
                datei >> variable;
                flt << variable;
                float fovx;
                flt >> fovx;
                flt.clear();

                Camera c{name, fovx};
                s.camera = c;

            }

            else if (variable.compare("renderer") == 0){

                datei >> name;
                std::string camname;//fals der renderer doch angepasst wird
                camname << name;
                datei >> name;
                std::string filename;
                name >> filename;
                datei >> flt;
                int xres;
                int yres;
                flt >> xres;
                flt.clear();
                datei >> flt;
                flt >> yres;
                flt.clear();

                Renderer r{filename, xres, yres};
                s.renderer = r;

            }

            else if (variable.compare("define") == 0){

                datei >> variable;

                if (variable.compare("material") == 0){

                }
                else if (variable.compare("light") == 0){

                }
                else if (variable.compare("shape") == 0){

                    datei >> variable;

                    if (variable.compare("box") == 0){

                    }

                    if (variable.compare("sphere") == 0){

                    }

                }

            }
        }



      }


    }
