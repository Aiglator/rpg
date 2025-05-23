#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "plateforme.hpp"

class World {
public:
    explicit World(const sf::Vector2u& windowSize);
    void draw(sf::RenderWindow& window);
    void scroll(float dx);
    sf::FloatRect getSolBounds() const;

private:
    std::vector<Plateforme> solBlocs;
};

#endif // WORLD_HPP
