#include "primitives.hpp"

#ifndef CAMERA_HPP
#define CAMERA_HPP

#define FOV 90

class Screen {
    public:

    Screen(Coords top_l, Coords bot_r, Coords normal);

    Coords get_coord(int x, int y);

    private:

    // Euclidean geometry so this should be doable
    Coords get_bot_left();
    Coords get_top_right();

    Coords top_left;
    Coords bot_right;

    // Calculate these now
    Coords top_right;
    Coords bot_left;

    Coords norm;
};

class Camera {

};

#endif