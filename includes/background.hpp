#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>

class background {
    public:
        background();
        void draw(sf::RenderWindow& window); // Corrected spelling here
    private:
        sf::Texture texture;
        sf::Sprite sprite;
};

#endif