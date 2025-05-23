#include "../includes/level1.hpp"
#include <random>
#include <ctime>
#include <SFML/Graphics/Texture.hpp>

Level1::Level1(const sf::Vector2u& windowSize) : bg(windowSize) {
    load();
}

void Level1::load() {
    // Largeur du niveau (plus long que l’écran)
    levelWidth = 3500.f; // <<< MODIFICATION : attribut de la classe !
    bg.setWidth(levelWidth);

    // Sol (plateforme principale)
    plateformes.emplace_back(sf::Vector2f(0.f, 560.f), sf::Vector2f(levelWidth, 40.f));

    // Plateformes fixes
    plateformes.emplace_back(sf::Vector2f(300.f, 460.f), sf::Vector2f(120.f, 20.f));
    plateformes.emplace_back(sf::Vector2f(500.f, 400.f), sf::Vector2f(120.f, 20.f));
    plateformes.emplace_back(sf::Vector2f(800.f, 350.f), sf::Vector2f(100.f, 20.f));
    plateformes.emplace_back(sf::Vector2f(1200.f, 500.f), sf::Vector2f(180.f, 20.f));
    plateformes.emplace_back(sf::Vector2f(1800.f, 350.f), sf::Vector2f(120.f, 20.f));

    // Plateformes basses supplémentaires (20 au total, espacées)
    float startY = 400.f; // juste sous le sol (sol = 560)
    float deltaY = 40.f;
    float startX = 100.f;
    float platformWidth = 120.f;
    float espaceX = (levelWidth - 2 * startX) / 20.f;

    for (int i = 0; i < 20; ++i) {
        float x = startX + i * espaceX;
        float y = startY + (i % 3) * deltaY; // effet escalier/alterné
        plateformes.emplace_back(sf::Vector2f(x, y), sf::Vector2f(platformWidth, 20.f));
    }

    // Coins
    coins.emplace_back(sf::Vector2f(350.f, 420.f));
    coins.emplace_back(sf::Vector2f(550.f, 360.f));
    coins.emplace_back(sf::Vector2f(830.f, 320.f));
    coins.emplace_back(sf::Vector2f(1850.f, 320.f));

    // Drapeau à la fin
    flagPos = sf::Vector2f(levelWidth - 100.f, 480.f);

    // === ENNEMIS ===
    float scaleY = 0.5f; // Scale utilisé dans Enemy.cpp !
    float spriteHeight = 16.f; // fallback par défaut
    sf::Texture tempTexture;
    if (tempTexture.loadFromFile("src/assets/goomba1.png")) {
        spriteHeight = tempTexture.getSize().y * scaleY;
    }
    float solY = 560.f; // Y du haut du sol principal
    float enemyY = solY - spriteHeight; // Pieds sur le sol

    float minX = 100.f;
    float maxX = levelWidth - 100.f;
    int nbEnemies = 3;

    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
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

// === AJOUTE CETTE MÉTHODE ===
float Level1::getLevelWidth() const {
    return levelWidth;
}
