#include "primitives.hpp"

#ifndef CAMERA_HPP
#define CAMERA_HPP

#define FOV 90

class Screen {
    public:

    Screen(Coords cent, Coords normal, Coords vertical, float w, float h);

    Coords get_coord(int x, int y);

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

class Camera {

};

#endif