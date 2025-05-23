#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Background {
public:
    Background(const sf::Vector2u& windowSize);

    void draw(sf::RenderWindow& window);
    void scroll(float dx);

    // Gestion largeur dynamique
    void setWidth(float newWidth);
    float getWidth() const;
    sf::FloatRect getBounds() const;

    sf::Vector2f getPosition() const { return backgroundShape.getPosition(); }
    sf::Vector2f getSize() const { return backgroundShape.getSize(); }
    void setPosition(const sf::Vector2f& pos) { backgroundShape.setPosition(pos); }

private:
    sf::Vector2u windowSize;
    sf::RectangleShape backgroundShape; // Fond bleu

    sf::Texture landscapeTexture;
    std::vector<sf::Sprite> landscapeSprites; // Scène répétée (montagnes)
    float landscapeWidth = 0.f;

    sf::Texture chateauTexture;
    std::unique_ptr<sf::Sprite> chateauSprite;

    void updateLandscapeSprites();
};

#endif // BACKGROUND_HPP
