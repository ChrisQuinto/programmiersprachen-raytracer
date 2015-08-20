#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/vec3.hpp>
#include <map>
#include "sdfloader.hpp"
#include "scene.hpp"
#include "material.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"


Sdfloader::Sdfloader(std::string file): file_{file}{}
Sdfloader::Sdfloader():file_{""} {}
Sdfloader::~Sdfloader(){}

Scene Sdfloader::loadscene(std::string file) const{

      std::ifstream datei(file, std::ios::in);
      Scene s{};

      std::string variable = " ";
      std::string name = " ";
      std::stringstream flt;
      if (datei.good()){
        std::cout << "im good" << std::endl;
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

                std::string camname;
                datei >> camname; //fals der renderer doch angepasst wird

                std::string filename;
                datei >> filename;

                datei >> variable;
                unsigned xres;
                unsigned yres;
                flt << variable;
                flt >> xres;
                flt.clear();
                datei >> variable;
                flt << variable;
                flt >> yres;
                flt.clear();

                Renderer r{xres, yres, filename};
                s.renderer = r;

            }

            else if (variable.compare("define") == 0){

                datei >> variable;

                if (variable.compare("material") == 0){

                    datei >> name;
                    float r,g,b;

                    datei >> variable;
                    flt << variable << ' ';
                    datei >> variable;
                    flt << variable << ' ';
                    datei >> variable;
                    flt << variable;
                    flt >> r >> g >> b;
                    Color ka(r,g,b);
                    flt.clear();

                    datei >> variable;
                    flt << variable << ' ';
                    datei >> variable;
                    flt << variable << ' ';
                    datei >> variable;
                    flt << variable;
                    flt >> r >> g >> b;
                    Color kd(r,g,b);
                    flt.clear();

                    datei >> variable;
                    flt << variable << ' ';
                    datei >> variable;
                    flt << variable << ' ';
                    datei >> variable;
                    flt << variable;
                    flt >> r >> g >> b;
                    Color ks(r,g,b);
                    flt.clear();

                    float m;
                    datei >> variable;
                    flt << variable;
                    flt >> m;
                    flt.clear();

                    Material mat{name, ka, kd, ks, m};
                    s.materials[name] = mat;
                }

                else if (variable.compare("amblight") == 0){

                    float r,g,b;

                    datei >> variable;
                    flt << variable << ' ';
                    datei >> variable;
                    flt << variable << ' ';
                    datei >> variable;
                    flt << variable;
                    flt >> r >> g >> b;
                    Color amb(r,g,b);
                    flt.clear();

                    s.amblight = amb;

                }

                else if (variable.compare("background") == 0){

                    float r,g,b;

                    datei >> variable;
                    flt << variable << ' ';
                    datei >> variable;
                    flt << variable << ' ';
                    datei >> variable;
                    flt << variable;
                    flt >> r >> g >> b;
                    Color back(r,g,b);
                    flt.clear();

                    s.background = back;
                }
                else if (variable.compare("light") == 0){

                    datei >> name;

                    float x, y, z;
                    datei >> variable;
                    flt << variable << ' ';
                    datei >> variable;
                    flt << variable << ' ';
                    datei >> variable;
                    flt << variable;
                    flt >> x >> y >> z;
                    glm::vec3 pos(x,y,z);
                    flt.clear();

                    float r, g, b;
                    datei >> variable;
                    flt << variable << ' ';
                    datei >> variable;
                    flt << variable << ' ';
                    datei >> variable;
                    flt << variable;
                    flt >> r >> g >> b;
                    Color ld(r,g,b);
                    flt.clear();


                    Light light(name, pos, ld);
                    s.lights.push_back(light);

                }
                else if (variable.compare("shape") == 0){

                    datei >> variable;

                    if (variable.compare("box") == 0){

                        datei >> name;
                        float x, y, z;
                        datei >> variable;
                        flt << variable << ' ';
                        datei >> variable;
                        flt << variable << ' ';
                        datei >> variable;
                        flt << variable;
                        flt >> x >> y >> z;
                        glm::vec3 p1(x,y,z);
                        flt.clear();

                        datei >> variable;
                        flt << variable << ' ';
                        datei >> variable;
                        flt << variable << ' ';
                        datei >> variable;
                        flt << variable;
                        flt >> x >> y >> z;
                        glm::vec3 p2(x,y,z);
                        flt.clear();

                        datei >> variable;

                        std::shared_ptr<Shape> b(new Box(p1, p2,name, s.materials[variable]));
                        s.shapes.push_back(b);

                    }

                    if (variable.compare("sphere") == 0){

                        datei >> name;

                        float x, y, z;
                        datei >> variable;
                        flt << variable << ' ';
                        datei >> variable;
                        flt << variable << ' ';
                        datei >> variable;
                        flt << variable;
                        flt >> x >> y >> z;
                        glm::vec3 pos(x,y,z);
                        flt.clear();

                        datei >> variable;
                        flt << variable;
                        float r;
                        flt >> r;

                        datei >> variable;

                        std::shared_ptr<Shape> sphere(new Sphere(pos, r,name, s.materials[variable]));
                        s.shapes.push_back(sphere);

                    }

                }

            }
        }



      }
      else if (datei.fail()){
          std::cout << "bad input" << std::endl;
      }
      else{
          std::cout << "no input my dear" << std::endl;
      }
      return s;

    }
