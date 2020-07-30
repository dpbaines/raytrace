#include "camera.hpp"

Screen::Screen(Coords top_l, Coords bot_r, Coords normal) : bot_right(bot_r), top_left(top_l), norm(normal) {
    
}

// Can't be fucked to learn about quaternions, maybe someday I can redo this to use those bad boys
Coords Screen::get_coord(int x, int y) {
    
}
