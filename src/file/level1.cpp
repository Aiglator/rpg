#include "../includes/level1.hpp"
#include <random>
#include <ctime>
#include <SFML/Graphics/Texture.hpp>

Level1::Level1(const sf::Vector2u& windowSize) : bg(windowSize) {
    load();
}

void Level1::load() {
    // Largeur du niveau
    levelWidth = 3500.f;
    bg.setWidth(levelWidth);

    // Sol (plateforme principale)
    plateformes.emplace_back(sf::Vector2f(0.f, 560.f), sf::Vector2f(levelWidth, 40.f));

    // Plateformes fixes
    plateformes.emplace_back(sf::Vector2f(300.f, 460.f), sf::Vector2f(120.f, 20.f));
    plateformes.emplace_back(sf::Vector2f(500.f, 400.f), sf::Vector2f(120.f, 20.f));
    plateformes.emplace_back(sf::Vector2f(800.f, 350.f), sf::Vector2f(100.f, 20.f));
    plateformes.emplace_back(sf::Vector2f(1200.f, 500.f), sf::Vector2f(180.f, 20.f));
    plateformes.emplace_back(sf::Vector2f(1800.f, 350.f), sf::Vector2f(120.f, 20.f));

    // Plateformes supplémentaires (20 au total)
    float startY = 400.f;
    float deltaY = 40.f;
    float startX = 100.f;
    float platformWidth = 120.f;
    float espaceX = (levelWidth - 2 * startX) / 20.f;
    for (int i = 0; i < 20; ++i) {
        float x = startX + i * espaceX;
        float y = startY + (i % 3) * deltaY;
        plateformes.emplace_back(sf::Vector2f(x, y), sf::Vector2f(platformWidth, 20.f));
    }

    // ======== Générer beaucoup de pièces ========
    coins.clear();
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_real_distribution<float> coinDistX(50.f, levelWidth - 50.f);
    std::uniform_real_distribution<float> coinDistY(250.f, 520.f); // Entre le haut et le sol

    for (int i = 0; i < 30; ++i) {
        float x = coinDistX(rng);
        float y = coinDistY(rng);
        coins.emplace_back(sf::Vector2f(x, y));
    }

    // Drapeau à la fin
    flagPos = sf::Vector2f(levelWidth - 100.f, 480.f);

    // ======== Générer beaucoup d'ennemis (Goombas sur le sol) ========
    float scaleY = 0.7f;
    float spriteHeight = 16.f;
    sf::Texture tempTexture;
    if (tempTexture.loadFromFile("src/assets/goomba1.png")) {
        spriteHeight = tempTexture.getSize().y * scaleY;
    }
    float solY = 600.f;
    float enemyY = solY - spriteHeight + 2.f; // +2 : bien posé au sol

    float minX = 100.f;
    float maxX = levelWidth - 100.f;
    int nbEnemies = 15; // Beaucoup plus d'ennemis

    std::uniform_real_distribution<float> dist(minX, maxX);
    enemies.clear();
    for (int i = 0; i < nbEnemies; ++i) {
        float x = dist(rng);
        enemies.emplace_back(sf::Vector2f(x, enemyY));
    }
}

Background& Level1::getBackground() { return bg; }
std::vector<Plateforme>& Level1::getPlateformes() { return plateformes; }
std::vector<Coin>& Level1::getCoins() { return coins; }
std::vector<Enemy>& Level1::getEnemies() { return enemies; }
sf::Vector2f Level1::getFlagPosition() const { return flagPos; }
float Level1::getLevelWidth() const { return levelWidth; }
