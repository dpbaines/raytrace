#include "primitives.hpp"
#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>

#ifndef CAMERA_HPP
#define CAMERA_HPP

#define FOV 90

class Screen {
    public:

    Screen(Coords cent, Coords normal, Coords vertical, float w, float h);

    Coords get_coord(int x, int y);
    Coords get_camera_pos();

    private:

    // Euclidean geometry so this should be doable
    Coords get_bot_left();
    Coords get_top_right();

    // Calculate these now
    Coords top_left;
    Coords bot_right;
    Coords top_right;
    Coords bot_left;

    Coords center;
    Coords vert;
    Coords norm;

    float width;
    float height;
};

struct Camera {

    // Initializes screen and camera using FOV define at top
    Camera(Coords cent, Coords normal, Coords vertical, float w, float h);

    Screen screen;
    Coords origin;
};

class Scene {
    public:

    void render();
    pixel cast_ray(const Scene& scene, Coords direction);

    void setup_camera();
    void add_shape(Shape& shape);

    private:

    // Sorted list based on distance to camera
    Camera camera;
    ShapeContainer shape_list;
};

// Gonna be taking advantage of polymorphism here to store different kinds of shapes in the same container
class ShapeContainer {
    public:

    void register_shape(Shape* shape, const Camera& camera);

    std::vector<Shape*> get_shape_list();

    private:

    bool compare_shape(const Shape* s1, const Shape* s2, const Camera& camera);
    void sort_container(const Camera& camera);

    // Sort this by distance from camera
    std::vector<Shape*> shape_cont;
};

#endif