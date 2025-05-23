#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <array>

class Enemy {
public:
    Enemy(const sf::Vector2f& pos);
    void update(float dt, const sf::Vector2f& playerPos);
    void draw(sf::RenderWindow& window);
    void stomped();
    bool isAlive() const;
    sf::FloatRect getBounds() const;

    // Accès direct aux textures (utile pour charger dans Level1 si besoin)
    static void loadTexturesIfNeeded();

private:
    sf::Vector2f position;
    int direction = 1;
    float speed = 40.f;
    bool alive = true;
    int animFrame = 0;
    float animTime = 0.f;

    sf::Sprite sprite;

    static std::array<sf::Texture, 3> goombaTextures;
    static bool texturesLoaded;

    void updateSprite();
};

#endif // ENEMY_HPP
