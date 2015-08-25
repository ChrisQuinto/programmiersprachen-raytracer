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
    ppm_(scene->camera.xres(), scene->camera.yres(), scene->filename) {}

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
  unsigned z = (scene_->camera.xres()/2)/(tan(scene_->camera.fovx()/360 * M_PI));
  for (unsigned y = 0; y < scene_->camera.yres(); ++y) {
      for (unsigned x = 0; x < scene_->camera.xres(); ++x) {
      glm::vec3 direction (-scene_->camera.xres()/2-0.5+x, -scene_->camera.yres()/2-0.5+y, z);
      Ray ray = scene_->camera.castray(direction);

      for (std::vector<std::shared_ptr<Shape>>::iterator i =scene_->shapes_ptr.begin();i != scene_->shapes_ptr.end();++i){
        *scene_->shapes_ptr[0].intersect(ray);
      }

      Pixel p(x,y);


      write(p);
    }
  }
  ppm_.save();
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
