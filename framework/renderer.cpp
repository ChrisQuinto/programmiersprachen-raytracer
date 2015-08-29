// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#define _USE_MATH_DEFINES
#include <math.h>
#include "renderer.hpp"

Renderer::Renderer(std::shared_ptr<Scene> scene) :
    scene_{scene},
    colorbuffer_(scene->camera.xres()*scene->camera.yres(), Color{}), //scene-> äquivalent zu (*scene).
    ppm_(scene->camera.xres(), scene->camera.yres(), scene->filename) {std::cout << "Konstruktor Aufruf fuer Renderer." << std::endl;
}

/*void Renderer::render()
{
  const std::size_t checkersize = 20;

  for (unsigned y = 0; y < scene_->camera.yres(); ++y) {
      for (unsigned x = 0; x < scene_->camera.xres(); ++x) {
      Pixel p(x,y);
      if ( ((x/checkersize)%2) != ((y/checkersize)%2)) {
          p.color = Color(0.0, 1.0, float(x) / scene_->camera.yres());
      } else {
          p.color = Color(1.0, 0.0, float(y) / scene_->camera.xres());
      }

      write(p);
    }
  }
  ppm_.save();
}*/

void Renderer::render()
{
    //z ist Entfernung der Camera zur Scene aus Winkel und Aufloesung berechnet
    int z = (scene_->camera.xres()/2)/(tan(scene_->camera.fovx()/360 * M_PI));
    std::cout << "\nMinimale Bildtiefe: " << -z << std::endl;
    for (int y = 0; y < scene_->camera.yres(); ++y) {
      for (int x = 0; x < scene_->camera.xres(); ++x) {
        Pixel p(x,y);
        glm::vec3 direction (-(scene_->camera.xres()/2) +0.5 + x, -(scene_->camera.yres()/2) + 0.5 + y, -z);
        Ray ray = scene_->camera.castray(direction);
        //std::cout << ray << std::endl;
        std::shared_ptr<Shape> first_hit;
        double shortest = 999999.9;
        for (std::vector<std::shared_ptr<Shape>>::iterator i = scene_->shapes_ptr.begin();i != scene_->shapes_ptr.end();++i){

          Hit hit = (*i)->intersect(ray);

          // std::map<std::shared_ptr<Shape>, float> shp;
          // std::shared_ptr<Shape> first_hit;

            if(hit.hit_ == true){
              if(hit.distance_ < shortest){
                shortest = hit.distance_;
                first_hit = hit.sptr_;

                Color color = (*first_hit).material().kd();
                //std::cout << ray <<' ' << hit << ' ' << color << std::endl;
                p.color = shade(ray, hit, color);
                //std::cout << color << std::endl;
              }
            }

        }
        if(shortest == 999999.9){
          p.color = (*scene_).background;
        }

      //std::cout << p.color << std::endl;
      write(p);
    }
  }
  ppm_.save();
}

Color Renderer::shade(Ray const& ray, Hit const& hit, Color color)
{
    for (std::vector<std::shared_ptr<Light>>::iterator i = scene_->lights.begin();i != scene_->lights.end();++i){

        Ray sunray((*i)->pos(), hit.intersection_ - (*i)->pos() );
        std::vector<Color> c;

        for (std::vector<std::shared_ptr<Shape>>::iterator j = scene_->shapes_ptr.begin();j != scene_->shapes_ptr.end();++j){

            Hit light_hit = (*j)->intersect(ray);
            if(light_hit.hit_ == true){
            continue;

/*                Color c_l = color * (*i)->dl() * (sqrt(pow(glm::dot(hit.normal_, sunvec),2))) + (*j)->material().ka() * (*scene_).amblight;
                //std::cout << sqrt(pow(glm::dot(hit.normal_, sunvec),2)) << std::endl;
                c.push_back(c_l);
                //std::cout << c_l << std::endl;
          }
=======
        } else {
>>>>>>> 0fc9960b78eeb8758e34247aaf45803833192c28*/

            glm::vec3 sunvec = glm::normalize((*i)->pos() - hit.intersection_);
            //std::cout << sunvec << std::endl;
            Color c_l = color * (*i)->dl() * (1-sqrt(pow(glm::dot(hit.normal_, sunvec),2))) /*+ (*j)->material().ka() * (*scene_).amblight*/;
            //std::cout << sqrt(pow(glm::dot(hit.normal_, sunvec),2)) << std::endl;
            c.push_back(c_l);
            //std::cout << c_l << std::endl;
            }
        }

        //glm::vec3 sunvec = glm::normalize((*i)->pos() - hit.intersection_);
        //glm::dot(hit.normal_, sunvec);
        //std::shared_ptr<Shape>
        Color kd_total (0.0,0.0,0.0);
        Color amb;
        amb.r = (*hit.sptr_).material().ka().r * (*scene_).amblight.r;
        amb.g = (*hit.sptr_).material().ka().g * (*scene_).amblight.g;
        amb.b = (*hit.sptr_).material().ka().b * (*scene_).amblight.b;
        int csize = sizeof(c);

        if(csize = 0){
            return amb;
            //std::cout << amb << std::endl;
        } else {
            for (std::vector<Color>::iterator k = c.begin();k != c.end();++k){
                kd_total += *k;
            }
        }

        kd_total = kd_total/sizeof(c);


      color = kd_total + amb;

      return color;
      //std::cout << color << std::endl;
    }
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
    size_t buf_pos = (scene_->camera.xres()*p.y + p.x);
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    colorbuffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}
