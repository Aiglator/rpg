#include "../../includes/world.hpp"

world::world() {
    // rien à faire ici si background est auto-chargé
}

void world::draw(sf::RenderWindow& window) {
    bg.draw(window); // utilise l'objet background
}
