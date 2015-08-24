#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/vec3.hpp>
#include <map>
#include "box.hpp"
#include "sdfloader.hpp"
#include "scene.hpp"
#include "material.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "sphere.hpp"
#include "renderer.hpp"

Sdfloader::Sdfloader() :
    file_{""} {}

Sdfloader::Sdfloader(std::string file) :
    file_{file} {}

Sdfloader::~Sdfloader() {}

Scene Sdfloader::loadscene(std::string file) const{

    std::ifstream datei(file, std::ios::in);

    std::string line, name;
    std::stringstream flt;

    std::string filename;
    Camera cam;
    Color amblight;
    Color background;
    std::map<std::string, std::shared_ptr<Material>> matmap;
    std::shared_ptr<Scene> scene_ptr;
    std::vector<std::shared_ptr<Light>> lightvec;
    std::vector<std::shared_ptr<Shape>> shapevec;

    if (datei.good()){
        std::cout << "File is good." << std::endl;
        while(datei >> line){
            if (line.compare("#") == 0 || line.compare("") == 0){
              continue;
            }

            else if (line.compare("renderer") == 0){

                datei >> filename;

                std::cout << "renderer worked \n";
            }

            else if (line.compare("camera") == 0){

                datei >> name;
                datei >> line;
                flt << line;
                float fovx;
                flt >> fovx;
                flt.clear();

                datei >> line;
                unsigned xres;
                unsigned yres;
                flt << line;
                flt >> xres;
                flt.clear();
                datei >> line;
                flt << line;
                flt >> yres;
                flt.clear();

                cam.name_ = name;
                cam.fovx_ = fovx;
                cam.xres_ = xres;
                cam.yres_ = yres;

                std::cout << "camera worked \n";
            }

            else if (line.compare("define") == 0){

                datei >> line;

                if (line.compare("material") == 0){

                    datei >> name;
                    float r,g,b;

                    datei >> line;
                    flt << line << ' ';
                    datei >> line;
                    flt << line << ' ';
                    datei >> line;
                    flt << line;
                    flt >> r >> g >> b;
                    Color ka(r,g,b);
                    flt.clear();

                    datei >> line;
                    flt << line << ' ';
                    datei >> line;
                    flt << line << ' ';
                    datei >> line;
                    flt << line;
                    flt >> r >> g >> b;
                    Color kd(r,g,b);
                    flt.clear();

                    datei >> line;
                    flt << line << ' ';
                    datei >> line;
                    flt << line << ' ';
                    datei >> line;
                    flt << line;
                    flt >> r >> g >> b;
                    Color ks(r,g,b);
                    flt.clear();

                    float m;
                    datei >> line;
                    flt << line;
                    flt >> m;
                    flt.clear();

                    std::shared_ptr<Material> temp_ptr = std::make_shared<Material>(Material{name,ka,kd,ks,m});
                    matmap.insert({name,temp_ptr});

                    /*Material mat{name, ka, kd, ks, m};
                    matmap[name] = mat;*/
                    std::cout << "material worked \n";
                }

                else if (line.compare("amblight") == 0){

                    float r,g,b;

                    datei >> line;
                    flt << line << ' ';
                    datei >> line;
                    flt << line << ' ';
                    datei >> line;
                    flt << line;
                    flt >> r >> g >> b;
                    Color amb(r,g,b);
                    flt.clear();

                    amblight = amb;

                    std::cout << "amblight worked \n";
                }

                else if (line.compare("background") == 0){

                    float r,g,b;

                    datei >> line;
                    flt << line << ' ';
                    datei >> line;
                    flt << line << ' ';
                    datei >> line;
                    flt << line;
                    flt >> r >> g >> b;
                    Color back(r,g,b);
                    flt.clear();

                    background = back;

                    std::cout << "background worked \n";
                }

                else if (line.compare("light") == 0){

                    datei >> name;

                    float x, y, z;
                    datei >> line;
                    flt << line << ' ';
                    datei >> line;
                    flt << line << ' ';
                    datei >> line;
                    flt << line;
                    flt >> x >> y >> z;
                    glm::vec3 pos(x,y,z);
                    flt.clear();

                    float r, g, b;
                    datei >> line;
                    flt << line << ' ';
                    datei >> line;
                    flt << line << ' ';
                    datei >> line;
                    flt << line;
                    flt >> r >> g >> b;
                    Color ld(r,g,b);
                    flt.clear();


                    std::shared_ptr<Light> light = std::make_shared<Light>(
                        Light{name, pos, ld}
                        );
                    lightvec.push_back(light);

                    std::cout << "light worked \n";
                }

                else if (line.compare("shape") == 0){

                    datei >> line;

                    if (line.compare("box") == 0){

                        datei >> name;
                        float x, y, z;
                        datei >> line;
                        flt << line << ' ';
                        datei >> line;
                        flt << line << ' ';
                        datei >> line;
                        flt << line;
                        flt >> x >> y >> z;
                        glm::vec3 p1(x,y,z);
                        flt.clear();

                        datei >> line;
                        flt << line << ' ';
                        datei >> line;
                        flt << line << ' ';
                        datei >> line;
                        flt << line;
                        flt >> x >> y >> z;
                        glm::vec3 p2(x,y,z);
                        flt.clear();

                        datei >> line;

                        std::shared_ptr<Shape> s_ptr = std::make_shared<Box>(
                            Box{ p1, p2, name, *matmap[line] }
                            );
                        shapevec.push_back(s_ptr);

                        std::cout << "box worked \n";
                    }

                    if (line.compare("sphere") == 0){

                        datei >> name;

                        float x, y, z;
                        datei >> line;
                        flt << line << ' ';
                        datei >> line;
                        flt << line << ' ';
                        datei >> line;
                        flt << line;
                        flt >> x >> y >> z;
                        glm::vec3 pos(x,y,z);
                        flt.clear();

                        datei >> line;
                        flt << line;
                        float r;
                        flt >> r;

                        datei >> line;

                        std::cout << "sphere eingelesen \n";

                        std::shared_ptr<Shape> sphere = std::make_shared<Sphere>(
                            Sphere{pos, r,name, *matmap[line]}
                            );
                        shapevec.push_back(sphere);

                        std::cout << "sphere worked \n";
                    }

                }

            }

        }

    }

      else if (datei.fail()){
          std::cout << "File is bad." << std::endl;
      }
      else{
          std::cout << "No file found." << std::endl;
      }

    std::cout << "all worked \n";
    Scene scene{
        filename,
        cam,
        amblight,
        background,
        matmap,
        lightvec,
        shapevec
    };
    return scene;

}
