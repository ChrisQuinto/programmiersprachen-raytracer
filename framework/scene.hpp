
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

<<<<<<< HEAD
    Camera camera_;
    Color amblight_;
    Color background_;
=======
    Camera camera;
    Color al;
    Color background;
>>>>>>> 74181cc8f9a68da184a486928e98efea851f9457
};

#endif
