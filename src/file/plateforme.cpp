#include "../includes/plateforme.hpp"

Plateforme::Plateforme(const sf::Vector2f& position, const sf::Vector2f& size) {
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color(139, 69, 19));
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(2.f);
}

void Plateforme::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

const sf::FloatRect Plateforme::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Plateforme::getSize() const {
    return shape.getSize();
}

bool Plateforme::contains(const sf::Vector2f& point) const {
    return shape.getGlobalBounds().contains(point);
}

void Plateforme::setPosition(const sf::Vector2f& pos) {
    shape.setPosition(pos);
}

sf::Vector2f Plateforme::getPosition() const {
    return shape.getPosition();
}

void Plateforme::move(const sf::Vector2f& offset) {
    shape.move(offset);
}
