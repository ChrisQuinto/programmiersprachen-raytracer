#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "shape.hpp"
#include "material.hpp"
#include "camera.hpp"
#include "renderer.hpp"
#include "light.hpp"

struct Scene
{
    Scene() :
    camera{Camera{}},
    amblight{Color{}},
    background{Color{}} {
        std::cout << "Scene built." << std::endl;
    }

    ~Scene() {}

    std::map<std::string, Material> materials;
    std::vector<std::shared_ptr <Shape>> shapes;
    std::vector<Light> lights;
    Camera camera;
    Color amblight;
    Color background;
};

#endif
