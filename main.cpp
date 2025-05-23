#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

#include "includes/level1.hpp"
#include "includes/world.hpp"
#include "includes/player.hpp"
#include "includes/coin.hpp"
#include "includes/enemy.hpp"

int main() {
    sf::Vector2u windowSize(800, 600);

    sf::RenderWindow window(sf::VideoMode(windowSize), "Mario 2D RPG");
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(100, 100));

    Level1 level(windowSize);
    Background& bg = level.getBackground();
    std::vector<Plateforme>& blocs = level.getPlateformes();
    std::vector<Coin>& coins = level.getCoins();
    std::vector<Enemy>& enemies = level.getEnemies();

    Player player(sf::Vector2f(100.f, 480.f));
    sf::Vector2f flagPos = level.getFlagPosition();

    // Limites du monde
    const float WORLD_LEFT_BOUND = 0.f;
    const float WORLD_RIGHT_BOUND = 3500.f;
    const float WORLD_TOP_BOUND = 0.f;
    const float WORLD_BOTTOM_BOUND = 600.f;

    // --- FlagPole (poteau du drapeau)
    sf::RectangleShape flagPoleShape(sf::Vector2f(8.f, 130.f));
    flagPoleShape.setFillColor(sf::Color(160, 160, 160));
    flagPoleShape.setPosition(sf::Vector2f(flagPos.x + 18.f, flagPos.y - 130.f));

    // --- Flag
    sf::Texture flagTexture;
    if (!flagTexture.loadFromFile("src/assets/flag.png")) {
        std::cerr << "[WARNING] flag.png introuvable." << std::endl;
    }
    sf::Sprite flagSprite(flagTexture);
    flagSprite.setScale(sf::Vector2f(0.3f, 0.3f));
    flagSprite.setPosition(sf::Vector2f(flagPos.x, flagPos.y - 130.f));

    // Animation de fin de niveau
    bool flagTouched = false;
    float flagDropY = flagPos.y - 130.f;
    float flagTargetY = flagPos.y - flagSprite.getGlobalBounds().size.y / 2.f;
    float flagSpeed = 120.f;

    // Police et texte pièces
    sf::Font font;
    if (!font.openFromFile("src/assets/font/font.ttf")) {
        std::cerr << "[WARNING] font.ttf introuvable." << std::endl;
    }
    sf::Text coinText(font, "");
    coinText.setCharacterSize(24);
    coinText.setFillColor(sf::Color::Yellow);
    coinText.setOutlineColor(sf::Color::Black);
    coinText.setOutlineThickness(2.f);
    coinText.setPosition(sf::Vector2f(10.f, 10.f));

    // --- Barre de vie
    sf::RectangleShape lifeBarBg(sf::Vector2f(150.f, 18.f));
    lifeBarBg.setFillColor(sf::Color(80, 80, 80));
    lifeBarBg.setPosition(sf::Vector2f(10.f, 45.f));
    sf::RectangleShape lifeBar(sf::Vector2f(140.f, 12.f));
    lifeBar.setFillColor(sf::Color(200, 0, 0));
    lifeBar.setPosition(sf::Vector2f(15.f, 49.f));

    // Camera
    sf::View camera(sf::FloatRect(
        sf::Vector2f(0.f, 0.f),
        sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y))
    ));

    sf::Clock clock;

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (!event.has_value()) continue;
            if (event->is<sf::Event::Closed>()) window.close();
        }

        float deltaTime = clock.restart().asSeconds();
        if (!flagTouched && player.isAlive()) player.handleInput();
        player.update(deltaTime, blocs, WORLD_RIGHT_BOUND);

        // Appliquer limites monde
        sf::Vector2f playerPos = player.getPosition();
        sf::FloatRect playerBounds = player.getBounds();
        bool positionChanged = false;

        if (playerBounds.position.x < WORLD_LEFT_BOUND) {
            playerPos.x = WORLD_LEFT_BOUND;
            positionChanged = true;
        }
        if (playerBounds.position.x + playerBounds.size.x > WORLD_RIGHT_BOUND) {
            playerPos.x = WORLD_RIGHT_BOUND - playerBounds.size.x;
            positionChanged = true;
        }
        if (playerBounds.position.y < WORLD_TOP_BOUND) {
            playerPos.y = WORLD_TOP_BOUND;
            positionChanged = true;
        }
        if (playerBounds.position.y > WORLD_BOTTOM_BOUND) {
            player.takeDamage(1); // Tomber = perte de vie
            playerPos = sf::Vector2f(100.f, 480.f);
            positionChanged = true;
        }
        if (positionChanged) player.setPosition(playerPos);

        // Ennemis
        for (auto& enemy : enemies) {
            enemy.update(deltaTime, player.getPosition());
        }

        // Collision joueur/ennemis
        for (auto& enemy : enemies) {
            if (!enemy.isAlive()) continue;
            if (player.getBounds().findIntersection(enemy.getBounds()).has_value()) {
                auto playerRect = player.getBounds();
                auto enemyRect = enemy.getBounds();
                float playerBottom = playerRect.position.y + playerRect.size.y;
                float enemyTop = enemyRect.position.y;
                if (player.getVelocity().y > 0 && playerBottom - enemyTop < 20.f) {
                    enemy.stomped();
                    player.bounce();
                } else {
                    player.takeDamage(1); // Collision classique = perte de vie
                }
            }
        }

        // Scroll background
        float dx = player.getVelocity().x * deltaTime;
        bg.scroll(-dx);

        // Animation & collision du drapeau
        if (!flagTouched && player.getBounds().findIntersection(flagSprite.getGlobalBounds()).has_value()) {
            flagTouched = true;
        }
        if (flagTouched && flagDropY < flagTargetY) {
            flagDropY += flagSpeed * deltaTime;
            if (flagDropY > flagTargetY) flagDropY = flagTargetY;
            flagSprite.setPosition(sf::Vector2f(flagPos.x, flagDropY));
        }

        // Camera suivant Mario (limitée)
        float levelWidth = WORLD_RIGHT_BOUND;
        float cameraX = player.getPosition().x + 100.f;
        float halfScreenWidth = static_cast<float>(windowSize.x) / 2.f;
        cameraX = std::max(halfScreenWidth, cameraX);
        cameraX = std::min(levelWidth - halfScreenWidth, cameraX);

        camera.setCenter(sf::Vector2f(
            cameraX,
            static_cast<float>(windowSize.y) / 2.f
        ));
        window.setView(camera);

        // Gestion pièces
        int coinsCollected = 0;
        for (auto& coin : coins) {
            coin.checkCollision(player.getBounds());
            if (coin.isCollected()) coinsCollected++;
        }

        // Barre de vie : width proportionnelle à la vie
        float maxLife = static_cast<float>(player.getMaxLife());
        float currentLife = static_cast<float>(player.getLife());
        float percent = (maxLife > 0) ? currentLife / maxLife : 0.f;
        lifeBar.setSize(sf::Vector2f(140.f * percent, 12.f));

        // --- Rendu ---
        window.clear(sf::Color(135, 206, 235)); // Ciel bleu
        bg.draw(window);
        for (auto& bloc : blocs) bloc.draw(window);
        for (auto& coin : coins) coin.draw(window);
        for (auto& enemy : enemies) enemy.draw(window);

        window.draw(flagPoleShape);
        window.draw(flagSprite);
        player.draw(window);

        // UI (vue fixe)
        window.setView(window.getDefaultView());
        coinText.setString("Coins: " + std::to_string(coinsCollected));
        window.draw(coinText);
        window.draw(lifeBarBg);
        window.draw(lifeBar);

        // Message game over si plus de vie
        if (!player.isAlive()) {
            sf::Text gameOverText(font, "GAME OVER");
            gameOverText.setCharacterSize(60);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition(sf::Vector2f(220.f, 250.f));
            window.draw(gameOverText);
        }

        window.display();
    }
    return 0;
}
