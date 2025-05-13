#include <SFML/Graphics.hpp>
#include <iostream>
#include "includes/background.hpp"

int main() {
    std::cout << "[INFO] Lancement du jeu Mario 2D RPG" << std::endl;

    // Dimensions de la fenêtre
    sf::Vector2u windowSize(800, 600);
    
    
    sf::RenderWindow window(sf::VideoMode(windowSize), "Mario 2D RPG");
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(100, 100));

    // Chargement du fond
    Background bg;
    bool backgroundVisible = bg.isValid();

    sf::RectangleShape fallback;
    if (!backgroundVisible) {
        std::cout << "[WARNING] background.png introuvable. Utilisation du fond de secours." << std::endl;
        fallback.setSize(sf::Vector2f(windowSize));
        fallback.setFillColor(sf::Color::Blue);
    } else {
        std::cout << "[INFO] Fond chargé avec succès." << std::endl;
    }

    std::cout << "[INFO] Début de la boucle principale." << std::endl;

    // Boucle principale
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                std::cout << "[INFO] Fermeture de la fenêtre." << std::endl;
                window.close();
            }
        }

        window.clear();

        if (backgroundVisible)
            bg.draw(window);
        else
            window.draw(fallback);

        window.display();
    }

    std::cout << "[INFO] Fin du jeu." << std::endl;
    return 0;
}
