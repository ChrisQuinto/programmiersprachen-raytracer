#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP
#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <iostream>
#include "shape.hpp"
#include "material.hpp"
#include "camera.hpp"
#include "light.hpp"

struct Scene
{
    Scene() :
    filename{"defaultscene.ppm"},
    camera{},
    amblight{},
    background{},
    materials{},
    lights{},
    shapes_ptr{} {
        std::cout << "Scene built." << std::endl;
    }

    Scene(
        std::string const& fname,
        Camera cam,
        Color const& al,
        Color const& bg,
        std::map<std::string, std::shared_ptr<Material>> materials_map,
        std::vector<std::shared_ptr<Light>> lights_vec,
        std::vector<std::shared_ptr<Shape>> shapes
    ) :
    filename{fname},
    camera{cam},
    amblight{al},
    background{bg},
    materials{},
    lights{},
    shapes_ptr{shapes} {
        materials.swap(materials_map);
        lights.swap(lights_vec);
    }

    ~Scene() {}

    Scene& operator=(Scene s2) {
        if (this == &s2) {
            return *this;
        }
        filename = s2.filename;
        camera = s2.camera;
        amblight = s2.amblight;
        background = s2.background;
        materials.swap(s2.materials);
        lights.swap(s2.lights);
        shapes_ptr = s2.shapes_ptr;
    }

    std::string filename;
    Camera camera;
    std::map<std::string, std::shared_ptr<Material>> materials;
    std::vector<std::shared_ptr<Shape>> shapes_ptr;
    std::vector<std::shared_ptr<Light>> lights;
    Color amblight;
    Color background;
};

#endif
