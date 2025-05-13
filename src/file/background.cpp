#include "../includes/background.hpp"
#include <iostream>

Background::Background() {
    if (!texture.loadFromFile("src/assets/background.png")) {
        std::cerr << "[ERREUR] Impossible de charger src/assets/background.png" << std::endl;
        valid = false;
        sprite = nullptr;
    } else {
        valid = true;
        sprite = new sf::Sprite(texture);

        // 🔁 Adapter la taille de l'image à la fenêtre (exemple : 1280x720)
        sf::Vector2u windowSize(1280, 720);  // À adapter si tu veux le passer dynamiquement
        sf::Vector2u textureSize = texture.getSize();

        float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
        
        sprite->setScale(sf::Vector2f(scaleX, scaleY));
    }
}

Background::~Background() {
    delete sprite;
    sprite = nullptr;
}

void Background::draw(sf::RenderWindow& window) {
    if (sprite) {
        window.draw(*sprite);
    }
}

bool Background::isValid() const {
    return valid;
}
