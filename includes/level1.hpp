#ifndef LEVEL1_HPP
#define LEVEL1_HPP

#include <vector>
#include <SFML/System/Vector2.hpp>
#include "background.hpp"
#include "plateforme.hpp"
#include "coin.hpp"
#include "enemy.hpp"

class Level1 {
public:
    Level1(const sf::Vector2u& windowSize);

    void load();
    Background& getBackground();
    std::vector<Plateforme>& getPlateformes();
    std::vector<Coin>& getCoins();
    std::vector<Enemy>& getEnemies();
    sf::Vector2f getFlagPosition() const;

    float getLevelWidth() const;   // <- AJOUT : accès à la largeur du niveau pour la caméra

private:
    Background bg;
    std::vector<Plateforme> plateformes;
    std::vector<Coin> coins;
    std::vector<Enemy> enemies;
    sf::Vector2f flagPos;
    float levelWidth = 3500.f;    // <- AJOUT : largeur du niveau
};

#endif // LEVEL1_HPP
