#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>
#include <vector>
#include <string>
#include "plateforme.hpp"

class Player {
public:
    enum class AnimState { Idle, Run, Jump };
    
    Player(const sf::Vector2f& startPos);
    void handleInput();
    void update(float deltaTime, const std::vector<Plateforme>& plateformes, float levelWidth);
    void updateSprite();
    void draw(sf::RenderWindow& window) const;
    void bounce();
    void setPosition(const sf::Vector2f& newPosition);

    // --- BARRE DE VIE ---
    void takeDamage(int amount);
    void heal(int amount);
    int getLife() const;
    int getMaxLife() const;
    bool isAlive() const;

    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    sf::Vector2f getVelocity() const;

    static void loadTexturesIfNeeded();

private:
    std::unique_ptr<sf::Sprite> sprite;
    sf::Vector2f velocity;
    bool isOnGround = false;
    float speed = 260.f;
    float jumpStrength = 440.f;
    float gravity = 1050.f;

    // Animation
    int animFrame = 0;
    float animTime = 0.f;
    AnimState animState = AnimState::Idle;
    bool facingLeft = false;

    // Vie du joueur
    int life = 100;
    int maxLife = 100;
    bool alive = true;

    static std::array<sf::Texture, 3> playerTextures;
    static bool texturesLoaded;
};

#endif // PLAYER_HPP
