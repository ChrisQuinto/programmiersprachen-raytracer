
#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP
#include <map>
#include <vector>
#include "shape.hpp"
#include "material.hpp"
#include "camera.hpp"
#include "renderer.hpp"

struct Scene
{
    Scene() :
    camera_{Camera{}},
    amblight_{Color{}},
    background_{Color{}} {}

    ~Scene() {}

    Camera camera_;
    Color amblight_;
    Color background_;
};

#endif
