// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include <glm/glm.hpp>
#include <string>
#include <memory>
#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "scene.hpp"

class Renderer
{
public:
    Renderer();
    Renderer(std::shared_ptr<Scene> scene, std::string const& file);

    void render();
    void write(Pixel const& p);

    inline std::vector<Color> const& colorbuffer() const
    {
      return colorbuffer_;
    }

private:
    std::shared_ptr<Scene> scene_;
    std::vector<Color> colorbuffer_;
    std::string filename_;
    PpmWriter ppm_;
};

#endif
