#include <SFML/Graphics.hpp>
#include "includes/background.hpp"

int main() {
    sf::Vector2u windowSize(800, 600);
    sf::RenderWindow window(sf::VideoMode(windowSize), "Mario 2D RPG");
    window.setFramerateLimit(60);

    Background bg;

    while (window.isOpen()) {
        // Pas de gestion d’événement ici

        window.clear();
        bg.draw(window);
        window.display();
    }

    return 0;
}
