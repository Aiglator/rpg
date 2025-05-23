#include "../includes/flag.hpp"
#include <iostream>

Flag::Flag(const sf::Vector2f& position, const std::string& texturePath, float scale) 
    : sprite(texture) // Initialize sprite with texture in the initialization list
{
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "[WARNING] " << texturePath << " introuvable." << std::endl;
    }
    sprite.setTexture(texture); // This line is now redundant but kept for clarity
    sprite.setScale(sf::Vector2f(scale, scale));
    sprite.setPosition(position);
}

void Flag::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Flag::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Flag::getPosition() const {
    return sprite.getPosition();
}

void Flag::setPosition(const sf::Vector2f& pos) {
    sprite.setPosition(pos);
}