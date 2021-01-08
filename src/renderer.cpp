#include "renderer.hpp"

Renderer::Renderer() {
    pix_array = new sf::Uint8[WIDTH * HEIGHT * 4];

    for (int i = 0; i < WIDTH * HEIGHT * 4; i += 4) {
        pix_array[i] = 0;
        pix_array[i + 1] = 0;
        pix_array[i + 2] = 0;
        pix_array[i + 3] = 255;
    }
}

Renderer::~Renderer() {
    delete[] pix_array;
}

pixel pixel::operator*(float& rhs) {
    return pixel(this->r * rhs, this->g * rhs, this->b * rhs, this->a * rhs);
}

pixel pixel::operator*(pixel& rhs) {
    return pixel(this->r * rhs.a, this->g * rhs.g, this->b * rhs.b, this->a * rhs.a);
}
    
pixel pixel::operator+(pixel& rhs) {
    return pixel(this->r + rhs.a, this->g + rhs.g, this->b + rhs.b, this->a + rhs.a);
}

void Renderer::set_pixel(pixel pix, int x, int y) {
    pix_array[4 * (x + y * WIDTH)] = pix.r;
    pix_array[4 * (x + y * WIDTH) + 1] = pix.g;
    pix_array[4 * (x + y * WIDTH) + 2] = pix.b;
    pix_array[4 * (x + y * WIDTH) + 3] = pix.a;
}

pixel Renderer::get_pixel(int x, int y) {
    pixel val;

    val.r = pix_array[4 * (x + y * WIDTH)];
    val.g = pix_array[4 * (x + y * WIDTH) + 1];
    val.b = pix_array[4 * (x + y * WIDTH) + 2];
    val.a = pix_array[4 * (x + y * WIDTH) + 3];

    return val;
}

sf::Uint8* Renderer::get_pixel_array() {
    return pix_array;
}