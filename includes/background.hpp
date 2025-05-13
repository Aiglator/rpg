#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>

/**
 * @brief Classe de gestion du fond d'écran du jeu.
 */
class Background {
public:
    Background(); ///< Constructeur par défaut (1280x720)
    Background(const sf::Vector2u& windowSize); ///< Constructeur avec taille de fenêtre dynamique
    ~Background(); ///< Destructeur propre

    void draw(sf::RenderWindow& window);
    bool isValid() const;

private:
    sf::Texture texture;      ///< Texture du fond
    sf::Sprite* sprite;       ///< Sprite affiché à l'écran
    bool valid = false;       ///< Booléen pour savoir si le chargement a réussi

    void scaleToWindow(const sf::Vector2u& windowSize); ///< Méthode interne pour le redimensionnement
};

#endif // BACKGROUND_HPP
