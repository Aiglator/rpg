#ifndef COIN_HPP
#define COIN_HPP

#include <SFML/Graphics.hpp>

class Coin {
public:
    Coin(const sf::Vector2f& position, float radius = 10.f);
    
    void draw(sf::RenderWindow& window) const;
    bool checkCollision(const sf::FloatRect& playerBounds) const;
    bool isCollected() const;

    // Ajouts pour l'édition :
    bool contains(const sf::Vector2f& point) const;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& pos);
    float getRadius() const;

private:
    sf::CircleShape shape;
    mutable bool collected = false;
};

#endif // COIN_HPP
