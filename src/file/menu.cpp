#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "menu.hpp"
#include <optional>

// Déclarations anticipées pour les fonctions de navigation
void level1();
void settings();

void viewmenu() {
    // Créer une fenêtre - SFML 3 utilise sf::VideoMode({width, height})
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");
    
    // Charger la police - Dans SFML 3, c'est openFromFile, pas loadFromFile
    sf::Font font;
    if (!font.openFromFile("fonts/arial.ttf")) {
        // Gérer l'erreur de chargement de police
        return;
    }
    
    // Créer les options du menu - Syntaxe du constructeur SFML 3
    sf::Text startGameText(font);
    startGameText.setString("Start Game");
    startGameText.setCharacterSize(50);
    startGameText.setFillColor(sf::Color::White);
    startGameText.setPosition({300.f, 200.f});
    
    sf::Text settingsText(font);
    settingsText.setString("Settings");
    settingsText.setCharacterSize(50);
    settingsText.setFillColor(sf::Color::White);
    settingsText.setPosition({300.f, 300.f});
    
    // Définir l'élément de menu sélectionné (0 = Start Game, 1 = Settings)
    int selectedItem = 0;
    
    // Définir l'icône de la fenêtre
    sf::Image icon;
    if (!icon.loadFromFile("icon.png")) {
        // Gérer l'erreur
    } else {
        // La méthode setIcon de SFML 3 prend directement l'image
        window.setIcon(icon);
    }
    
    // Boucle principale
    while (window.isOpen()) {
        // Gestion des événements SFML 3 - syntaxe complètement différente !
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            
            // Gestion des clics de souris
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                // Vérifier si le clic est sur le bouton "Start Game"
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    // Convertir la position du clic en coordonnées de flottants
                    sf::Vector2f mousePos = {static_cast<float>(mousePressed->position.x), 
                                          static_cast<float>(mousePressed->position.y)};
                    
                    // Vérifier si le clic est sur le bouton "Start Game"
                    if (startGameText.getGlobalBounds().contains(mousePos)) {
                        // Clic sur Start Game
                        window.close();
                        level1(); // Assurez-vous que cette fonction est implémentée
                    }
                    
                    // Vérifier si le clic est sur le bouton "Settings"
                    if (settingsText.getGlobalBounds().contains(mousePos)) {
                        // Clic sur Settings
                        window.close();
                        settings(); // Assurez-vous que cette fonction est implémentée
                    }
                }
            }
            
            // Gestion des touches du clavier
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Up) {
                    selectedItem = 0; // Déplacer à Start Game
                    startGameText.setFillColor(sf::Color::Red);
                    settingsText.setFillColor(sf::Color::White);
                }
                else if (keyPressed->code == sf::Keyboard::Key::Down) {
                    selectedItem = 1; // Déplacer à Settings
                    startGameText.setFillColor(sf::Color::White);
                    settingsText.setFillColor(sf::Color::Red);
                }
                else if (keyPressed->code == sf::Keyboard::Key::Enter) {
                    if (selectedItem == 0) {
                        // Start Game - transition vers level1.cpp
                        window.close();
                        level1(); // Assurez-vous que cette fonction est implémentée
                    } else {
                        // Settings - transition vers settings.cpp
                        window.close();
                        settings(); // Assurez-vous que cette fonction est implémentée
                    }
                }
            }
        }
        
        // Effet de survol pour les boutons du menu
        sf::Vector2f mousePos = {static_cast<float>(sf::Mouse::getPosition(window).x),
                               static_cast<float>(sf::Mouse::getPosition(window).y)};
        
        // Effet de survol pour Start Game
        if (startGameText.getGlobalBounds().contains(mousePos)) {
            if (selectedItem != 0) { // Ne pas changer la couleur si déjà sélectionné par clavier
                startGameText.setFillColor(sf::Color::Red);
                selectedItem = 0;
            }
        } else if (selectedItem != 0) {
            startGameText.setFillColor(sf::Color::White);
        }
        
        // Effet de survol pour Settings
        if (settingsText.getGlobalBounds().contains(mousePos)) {
            if (selectedItem != 1) { // Ne pas changer la couleur si déjà sélectionné par clavier
                settingsText.setFillColor(sf::Color::Red);
                selectedItem = 1;
            }
        } else if (selectedItem != 1) {
            settingsText.setFillColor(sf::Color::White);
        }
        
        // Effacer l'écran
        window.clear(sf::Color::Black);
        
        // Dessiner les éléments du menu
        window.draw(startGameText);
        window.draw(settingsText);
        
        // Afficher
        window.display();
    }
}