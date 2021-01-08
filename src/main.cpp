#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "RayConfig.h"
#include "renderer.hpp"
#include "primitives.hpp"
#include "camera.hpp"

int main() {
    std::cout << "Davids Raytracing VERSION: " << Raytrace_VERSION_MAJOR << "." << Raytrace_VERSION_MINOR << std::endl;

    sf::RenderWindow window(sf::VideoMode(200, 200), "Ray Tracing App");
    window.clear(sf::Color::Black);

    Renderer renderer;
    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);

    sf::Sprite sprite(texture);

    Scene scene(Coords(0, 0, 0), Coords(0, 1, 0), Coords(0, 0, 1), 1.6, 1.2);

    Sphere sp1(1, Coords(0, 5, 0));
    sp1.reflectivity = 1;
    sp1.emissivity = pixel(255, 255, 0, 100);

    Plane p1(Coords(0, 0, 1), Coords(0, 0, -2));
    p1.reflectivity = 1;

    Sphere light(1, Coords(1, 1, -2));
    light.emissivity = pixel(255, 255, 255, 255);

    scene.add_shape(&sp1);
    scene.add_shape(&p1);
    scene.add_light(&light);

    scene.render(renderer, 10, 3);

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