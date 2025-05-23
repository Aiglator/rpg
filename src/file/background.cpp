#include "../includes/background.hpp"
#include <iostream>
#include <cmath>

Background::Background(const sf::Vector2u& windowSize) : windowSize(windowSize) {
    // Fond bleu : largeur initiale, adapter si monde plus large
    backgroundShape.setPosition({0.f, 0.f});
    backgroundShape.setSize(sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));
    backgroundShape.setFillColor(sf::Color(135, 206, 235)); // bleu ciel

    if (landscapeTexture.loadFromFile("src/assets/landscape.png")) {
        updateLandscapeSprites();
    } else {
        std::cerr << "[WARNING] landscape.png introuvable." << std::endl;
    }

    if (chateauTexture.loadFromFile("src/assets/chateau_cropped.png")) {
        chateauSprite = std::make_unique<sf::Sprite>(chateauTexture);
        chateauSprite->setScale(sf::Vector2f(4.f, 4.f));
        chateauSprite->setPosition(sf::Vector2f(static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) - 200.f));
    } else {
        std::cerr << "[WARNING] chateau_cropped.png introuvable." << std::endl;
    }
}

void Background::updateLandscapeSprites() {
    landscapeSprites.clear();

    if (!landscapeTexture.getSize().x || !landscapeTexture.getSize().y)
        return;

    float curWidth = backgroundShape.getSize().x;
    float scaleX = curWidth / landscapeTexture.getSize().x;
    float scaleY = backgroundShape.getSize().y / landscapeTexture.getSize().y;
    landscapeWidth = landscapeTexture.getSize().x * scaleX;

    int nbSprites = std::ceil(curWidth / landscapeWidth) + 2;
    for (int i = 0; i < nbSprites; ++i) {
        sf::Sprite sprite(landscapeTexture);
        sprite.setScale(sf::Vector2f(scaleX, scaleY));
        sprite.setPosition(sf::Vector2f(i * landscapeWidth, 0.f));
        landscapeSprites.push_back(sprite);
    }
}

void Background::draw(sf::RenderWindow& window) {
    window.draw(backgroundShape);
    for (const auto& sprite : landscapeSprites)
        window.draw(sprite);

    if (chateauSprite)
        window.draw(*chateauSprite);
}

void Background::scroll(float dx) {
    float dxScroll = dx * 0.5f;

    for (auto& sprite : landscapeSprites)
        sprite.move(sf::Vector2f(dxScroll, 0));

    // Scroll infini (optionnel, utile si tu fais un runner infini)
    for (auto& sprite : landscapeSprites) {
        if (sprite.getPosition().x + landscapeWidth < 0.f) {
            float maxX = 0.f;
            for (const auto& s : landscapeSprites)
                if (s.getPosition().x > maxX)
                    maxX = s.getPosition().x;

            sprite.setPosition(sf::Vector2f(maxX + landscapeWidth, 0.f));
        }
    }

    if (chateauSprite)
        chateauSprite->move(sf::Vector2f(dx * 0.3f, 0));
}

void Background::setWidth(float newWidth) {
    if (newWidth < 100.f) newWidth = 100.f;
    backgroundShape.setSize({ newWidth, static_cast<float>(windowSize.y) });
    updateLandscapeSprites();
    if (chateauSprite)
        chateauSprite->setPosition(sf::Vector2f(newWidth / 2.f, backgroundShape.getSize().y - 200.f));
}

float Background::getWidth() const {
    return backgroundShape.getSize().x;
}

sf::FloatRect Background::getBounds() const {
    return backgroundShape.getGlobalBounds();
}
