#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#ifndef RENDERER_HPP
#define RENDERER_HPP

#define HEIGHT 600
#define WIDTH 800

struct pixel {
    uint r;
    uint g;
    uint b;
    uint a;

    pixel() {};
    pixel(uint r1, uint g1, uint b1, uint a1) : r(r1), g(g1), b(b1), a(a1) {};

    pixel operator*(float& rhs);
    pixel operator*(pixel& rhs);
    
    pixel operator+(pixel& rhs);

};

class Renderer {
    public:

    Renderer();
    ~Renderer();

    void set_pixel(pixel pix, int x, int y);
    pixel get_pixel(int x, int y);

    sf::Uint8* get_pixel_array();

    private:
    sf::Uint8 *pix_array;
};

#endif