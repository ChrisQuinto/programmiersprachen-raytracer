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
#include <fstream>

#include "renderer.hpp"

Renderer::Renderer(std::shared_ptr<Scene> scene) :
    scene_{scene},
    colorbuffer_(scene->camera.xres()*scene->camera.yres(), Color{}), //scene-> äquivalent zu (*scene).
    ppm_(scene->camera.xres(), scene->camera.yres(), scene->filename) {
    //std::cout << "Konstruktor Aufruf fuer Renderer." << std::endl;
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
    //std::cout << "\nMinimale Bildtiefe: " << -z << std::endl;
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
                        p.color = shade(ray, hit);
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



Color Renderer::shade(Ray const& ray, Hit const& hit)
{
  Color kd = (*hit.sptr_).material().kd();
  Color ks = (*hit.sptr_).material().ks();
  Color ka = (*hit.sptr_).material().ka();
  Color ip;
  Color ld_ls;
  Color l;

  float winkela;
  float winkelb;
  float shadowbias = 0.009f ;

  std::vector<Color> ip_vec;
  std::vector<float> wa_vec;
  std::vector<float> wb_vec;


  glm::vec3 norm = glm::normalize(hit.normal_);
  glm::vec3 rref;
  glm::vec3 ray_inv_dir = glm::normalize(-ray.direction_);
  glm::vec3 sunvec;

  Color la = ka * (*scene_).amblight;;

  for (std::vector<std::shared_ptr<Light>>::iterator i = scene_->lights.begin();i != scene_->lights.end();++i){

    Ray sunray(hit.intersection_ + (shadowbias*norm) ,(*i)->pos() - (hit.intersection_ + (shadowbias * norm) ));

    for (std::vector<std::shared_ptr<Shape>>::iterator j = scene_->shapes_ptr.begin();j != scene_->shapes_ptr.end();++j){

      Hit light_hit = (*j)->intersect(sunray);
      sunvec = (*i)->pos() - hit.intersection_;

      if(light_hit.distance_ < (sqrt((pow(sunvec.x, 2) + pow(sunvec.y, 2) + pow(sunvec.z,2))))) {

          ip = {0.0,0.0,0.0};
          winkela = 0.0;
          winkelb = 0.0;

          break;



      }

      else{

        ip = (*i)->dl();
        glm::vec3 norm_sunvec = glm::normalize(sunvec);
        winkela = sqrt(pow(glm::dot(norm, norm_sunvec),2));
        //winkelb = pow(glm::dot(ray_inv_dir, sunvec))-(2*winkela)), (*hit.sptr_).material().m() );
        //std::cout << ip << std::endl;

        rref = 2.0f * winkela * norm - norm_sunvec;
        winkelb = glm::dot(rref,ray_inv_dir);

      }

    }
    //std::cout << ip << std::endl;
    ip_vec.push_back(ip);
    wa_vec.push_back(winkela);
    wb_vec.push_back(pow(winkelb, hit.sptr_->material().m() ));

    ip = {0.0,0.0,0.0};
    winkela = 0.0;
    winkelb = 0.0;
    sunvec = {0.0,0.0,0.0};
  }
  for(int t = 0; t < ip_vec.size(); ++t){

    ld_ls = ld_ls + (ip_vec[t]*((kd*wa_vec[t]) + (ks*wb_vec[t])));

    //std::cout << t << std::endl;
    //std::cout << wa_vec[t] << std::endl;
    //std::cout << wb_vec[t] << std::endl << std::endl;

  }

l = ld_ls + la;
//std::cout << la << std::endl;
return l;


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
