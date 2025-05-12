#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>

class Background {
public:
    Background();                             // constructeur
    void draw(sf::RenderWindow& window);      // méthode d'affichage

private:
    sf::Texture texture;
    sf::Sprite sprite;
    
};

#endif
