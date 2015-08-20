
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
    camera{Camera{}},
    amblight{Color{}},
    background{Color{}},
    renderer{Renderer{}}

    {}

    ~Scene() {}
    std::map<std::string, Material> material;
    std::vector<Light> lights;
    Camera camera;
    Color amblight;
    Color background;
    Renderer renderer;
};

#endif
