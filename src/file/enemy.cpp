#include "../includes/enemy.hpp"
#include <iostream>
#include <cmath>

// Définition des statiques
std::array<sf::Texture, 3> Enemy::goombaTextures;
bool Enemy::texturesLoaded = false;

// Le constructeur
Enemy::Enemy(const sf::Vector2f& pos)
    : position(pos), sprite([&]{
        loadTexturesIfNeeded();
        return sf::Sprite(goombaTextures[0]);
    }())
{
    sprite.setScale(sf::Vector2f(0.4f, 0.4f)); // taille réduite X5
    sprite.setPosition(position);
}

void Enemy::loadTexturesIfNeeded() {
    if (texturesLoaded) return;
    if (!goombaTextures[0].loadFromFile("src/assets/goomba1.png"))
        std::cerr << "[WARNING] goomba1.png introuvable" << std::endl;
    if (!goombaTextures[1].loadFromFile("src/assets/goomba2.png"))
        std::cerr << "[WARNING] goomba2.png introuvable" << std::endl;
    if (!goombaTextures[2].loadFromFile("src/assets/goomba3.png"))
        std::cerr << "[WARNING] goomba3.png introuvable" << std::endl;
    texturesLoaded = true;
}

void Enemy::update(float dt, const sf::Vector2f& playerPos) {
    if (!alive) return;

    // Animation
    animTime += dt;
    if (animTime > 0.25f) {
        animTime = 0.f;
        animFrame = 1 - animFrame;
        updateSprite();
    }

    // Patrouille
    position.x += direction * speed * dt;
    if (position.x < 0.f) direction = 1;
    if (position.x > 3400.f) direction = -1;

    // Réagit à la proximité du joueur
    float dist = std::abs(playerPos.x - position.x);
    if (dist < 200.f) {
        direction = (playerPos.x > position.x) ? 1 : -1;
    }

    sprite.setPosition(position);
}

void Enemy::updateSprite() {
    if (!alive) {
        sprite.setTexture(goombaTextures[2]); // Texture écrasé
    } else {
        sprite.setTexture(goombaTextures[animFrame]); // Marche gauche/droite
    }
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Enemy::getBounds() const {
    return sprite.getGlobalBounds();
}

void Enemy::stomped() {
    alive = false;
    updateSprite();
}

bool Enemy::isAlive() const {
    return alive;
}
