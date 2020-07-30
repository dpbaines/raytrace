#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#ifndef RENDERER_HPP
#define RENDERER_HPP

#define HEIGHT 600
#define WIDTH 800

struct pixel {
    sf::Uint8 r;
    sf::Uint8 g;
    sf::Uint8 b;
    sf::Uint8 a;

    pixel() {};
    pixel(sf::Uint8 r1, sf::Uint8 g1, sf::Uint8 b1, sf::Uint8 a1) : r(r1), g(g1), b(b1), a(a1) {};
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