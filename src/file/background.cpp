#include "../includes/background.hpp"
#include <iostream>

Background::Background() : sprite(texture) {
    if (!texture.loadFromFile("src/assets/background.png")) {
        std::cerr << "Erreur de chargement background.png" << std::endl;
    }
}

void Background::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
