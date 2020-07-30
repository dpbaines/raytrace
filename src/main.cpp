#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "RayConfig.h"
#include "renderer.hpp"
#include "primitives.hpp"

int main() {
    std::cout << "Davids Raytracing VERSION: " << Raytrace_VERSION_MAJOR << "." << Raytrace_VERSION_MINOR << std::endl;

    sf::RenderWindow window(sf::VideoMode(200, 200), "Ray Tracing App");
    window.clear(sf::Color::Black);

    Renderer renderer;
    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);

    sf::Sprite sprite(texture);

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        texture.update(renderer.get_pixel_array());
        window.draw(sprite);

        window.display();
    }
    
    return 0;
}