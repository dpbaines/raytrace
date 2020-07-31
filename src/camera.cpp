#include "camera.hpp"

Screen::Screen(Coords cent, Coords normal, Coords vertical, float w, float h) : center(cent), norm(normal), vert(vertical), height(h), width(w) {
    // First lets calculate the corners using some !!LINEAR ALGEBRA!!

    norm.normalize();
    vert.normalize();

    // Cross product will give vector in direction of right
    Coords perp = norm % vert;
    
    // Redundant but make sure
    perp.normalize();

    top_right = center + (perp * (width / 2)) + (vert * (height / 2));
    top_left  = center + (perp * (-width / 2)) + (vert * (height / 2));

    bot_right = center + (perp * (width / 2)) + (vert * (-height / 2));
    bot_left  = center + (perp * (-width / 2)) + (vert * (-height / 2));
}

// Can't be fucked to learn about quaternions, maybe someday I can redo this to use those bad boys
// Index (0,0) is the top left
Coords Screen::get_coord(int x, int y) {
    Coords lefttoright = top_right - top_left;
    Coords toptobot = top_left - bot_left;

    Coords ans = top_left + (lefttoright * ( (float) x / WIDTH )) + (toptobot * ( (float) y / HEIGHT ));

    return ans;
}
