#include "../includes/coin.hpp"

Coin::Coin(const sf::Vector2f& position, float radius)
{
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Yellow);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(2.f);
    // On centre la pièce pour l'édition (axe du cercle)
    shape.setPosition(position - sf::Vector2f(radius, radius));
}

void Coin::draw(sf::RenderWindow& window) const {
    if (!collected)
        window.draw(shape);
}

bool Coin::checkCollision(const sf::FloatRect& playerBounds) const {
    if (!collected && playerBounds.findIntersection(shape.getGlobalBounds()).has_value()) {
        collected = true; // mutable → autorisé dans const
        return true;
    }
    return false;
}

bool Coin::isCollected() const {
    return collected;
}

// === Pour édition ===
bool Coin::contains(const sf::Vector2f& point) const {
    sf::Vector2f center = getPosition();
    float distSq = (point.x - center.x) * (point.x - center.x) + (point.y - center.y) * (point.y - center.y);
    return distSq < (shape.getRadius() * shape.getRadius());
}

sf::Vector2f Coin::getPosition() const {
    return shape.getPosition() + sf::Vector2f(shape.getRadius(), shape.getRadius());
}

void Coin::setPosition(const sf::Vector2f& pos) {
    shape.setPosition(pos - sf::Vector2f(shape.getRadius(), shape.getRadius()));
}

float Coin::getRadius() const {
    return shape.getRadius();
}
