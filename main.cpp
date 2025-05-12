#include <SFML/Graphics.hpp>
#include "includes/world.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mario 2D RPG");
    window.setFramerateLimit(60);

    world w;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        w.draw(window);
        window.display();
    }

    return 0;
}
