#ifndef FLAG_HPP
#define FLAG_HPP

#include <SFML/Graphics.hpp>

class Flag {
public:
    Flag(const sf::Vector2f& position, const std::string& texturePath = "src/assets/flag.png", float scale = 0.3f);

    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& pos);

    bool isReached = false;

private:
    sf::Texture texture;
    sf::Sprite sprite; // <- ceci est correct !
};

#endif // FLAG_HPP
// Flag.hpp
//Message dévelloppeur rayan je voulais mettre une blague j'ai pas put 
// d'ailleurs si quelqu'un lis le message mario a un gros nez c'est fait exprés 