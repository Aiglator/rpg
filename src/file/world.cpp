#include "../includes/world.hpp"
#include <SFML/Graphics.hpp>

const float blocWidth = 200.f; // Largeur d’un bloc de sol (ajuste si nécessaire)

World::World(const sf::Vector2u& windowSize) {
    float y = static_cast<float>(windowSize.y) - 50.f;

    // Crée plusieurs blocs alignés horizontalement
    for (int i = 0; i < 5; ++i) {
        float x = i * blocWidth;
        solBlocs.emplace_back(sf::Vector2f(x, y), sf::Vector2f(blocWidth, 50.f));
    }
}

void World::draw(sf::RenderWindow& window) {
    for (auto& bloc : solBlocs)
        bloc.draw(window);
}

void World::scroll(float dx) {
    for (auto& bloc : solBlocs)
        bloc.move(sf::Vector2f(dx, 0.f));

    for (auto& bloc : solBlocs) {
        if (bloc.getPosition().x + blocWidth <= 0.f) {
            // Trouver la position la plus à droite
            float maxX = 0.f;
            for (const auto& b : solBlocs) {
                maxX = std::max(maxX, b.getPosition().x);
            }

            // Aligner exactement après le plus à droite
            bloc.setPosition(sf::Vector2f(maxX + blocWidth, bloc.getPosition().y));
        }
    }
}

sf::FloatRect World::getSolBounds() const {
    // On retourne les bounds du premier bloc pour collision
    if (!solBlocs.empty())
        return solBlocs[0].getBounds();

    return sf::FloatRect();
}
