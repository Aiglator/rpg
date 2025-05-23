#ifndef PLATEFORME_HPP
#define PLATEFORME_HPP

#include <SFML/Graphics.hpp>

class Plateforme {
public:
    Plateforme(const sf::Vector2f& position, const sf::Vector2f& size = {100.f, 20.f});
    void draw(sf::RenderWindow& window) const;
    const sf::FloatRect getBounds() const;
    sf::Vector2f getSize() const;

    bool contains(const sf::Vector2f& point) const;
    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition() const;
    void move(const sf::Vector2f& offset);

private:
    sf::RectangleShape shape;
};

#endif // PLATEFORME_HPP
