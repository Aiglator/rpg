#include "../includes/player.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

// Initialisation statique
std::array<sf::Texture, 3> Player::playerTextures;
bool Player::texturesLoaded = false;

void Player::loadTexturesIfNeeded() {
    if (texturesLoaded) return;

    std::vector<std::string> paths = {
        "src/assets/idlemario.png",
        "src/assets/runmario1.png",
        "src/assets/jumpmario.png"
    };
    for (int i = 0; i < 3; i++) {
        if (!playerTextures[i].loadFromFile(paths[i])) {
            std::cerr << "[ERREUR CRITIQUE] " << paths[i] << " introuvable!" << std::endl;
        }
    }
    texturesLoaded = true;
}

Player::Player(const sf::Vector2f& startPos) {
    loadTexturesIfNeeded();
    sprite = std::make_unique<sf::Sprite>(playerTextures[0]);
    sprite->setScale(sf::Vector2f(0.3f, 0.3f));
    sprite->setPosition(startPos);

    velocity = sf::Vector2f(0.f, 0.f);
    animFrame = 0;
    animTime = 0.f;
    animState = AnimState::Idle;
    facingLeft = false;

    // Initialisation de la vie
    life = maxLife = 3;
    alive = true;
}

void Player::handleInput() {
    velocity.x = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        velocity.x -= speed;
        facingLeft = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        velocity.x += speed;
        facingLeft = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && isOnGround) {
        velocity.y = -jumpStrength;
        isOnGround = false;
    }
}

void Player::update(float deltaTime, const std::vector<Plateforme>& plateformes, float levelWidth) {
    velocity.y += gravity * deltaTime;
    isOnGround = false;
    sprite->move(velocity * deltaTime);

    // === COLLISION AVEC LES PLATEFORMES ===
    for (const auto& plateforme : plateformes) {
        auto pRect = plateforme.getBounds();
        auto playerRect = sprite->getGlobalBounds();

        // Correction : intersection avec findIntersection et position/size
        if (playerRect.findIntersection(pRect).has_value()) {
            float playerPrevBottom = playerRect.position.y + playerRect.size.y - velocity.y * deltaTime;
            float plateformeTop = pRect.position.y;

            if (velocity.y > 0.f && playerPrevBottom <= plateformeTop + 2.f) {
                sprite->setPosition(sf::Vector2f(sprite->getPosition().x, plateformeTop - playerRect.size.y));
                velocity.y = 0.f;
                isOnGround = true;
            }
        }
    }

    // === LIMITES DU MONDE (MURS INVISIBLES) ===
    sf::Vector2f pos = sprite->getPosition();
    auto bounds = sprite->getGlobalBounds();
    bool positionChanged = false;

    // Mur gauche
    if (pos.x < 0.f) {
        pos.x = 0.f;
        positionChanged = true;
    }
    // Mur droit
    if (pos.x + bounds.size.x > levelWidth) {
        pos.x = levelWidth - bounds.size.x;
        positionChanged = true;
    }
    // Mur du haut
    if (pos.y < 0.f) {
        pos.y = 0.f;
        positionChanged = true;
    }
    // Mur du bas (respawn si Mario tombe)
    if (pos.y > 600.f) {
        pos = sf::Vector2f(100.f, 480.f); // Position de spawn
        velocity = sf::Vector2f(0.f, 0.f); // Reset de la vitesse
        positionChanged = true;
    }
    if (positionChanged) {
        sprite->setPosition(pos);
    }

    // === ANIMATION ===
    if (!isOnGround)
        animState = AnimState::Jump;
    else if (velocity.x != 0)
        animState = AnimState::Run;
    else
        animState = AnimState::Idle;

    if (animState == AnimState::Run) {
        animTime += deltaTime;
        if (animTime > 0.15f) {
            animTime = 0.f;
            animFrame = 1 - animFrame;
        }
    } else {
        animFrame = 0;
    }
    updateSprite();
}

void Player::updateSprite() {
    switch (animState) {
        case AnimState::Idle:
            sprite->setTexture(playerTextures[0]);
            break;
        case AnimState::Run:
            sprite->setTexture(animFrame == 0 ? playerTextures[1] : playerTextures[0]);
            break;
        case AnimState::Jump:
            sprite->setTexture(playerTextures[2]);
            break;
    }
    float scaleX = facingLeft ? -0.3f : 0.3f;
    sprite->setScale(sf::Vector2f(scaleX, 0.3f));
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(*sprite);
}

void Player::bounce() {
    velocity.y = -jumpStrength / 5.5f;
}

void Player::setPosition(const sf::Vector2f& newPosition) {
    sprite->setPosition(newPosition);
}

// === GESTION DE LA VIE ===
void Player::takeDamage(int amount) {
    if (!alive) return;
    life -= amount;
    if (life <= 0) {
        life = 0;
        alive = false;
    }
}

void Player::heal(int amount) {
    life += amount;
    if (life > maxLife) life = maxLife;
}

int Player::getLife() const {
    return life;
}

int Player::getMaxLife() const {
    return maxLife;
}

bool Player::isAlive() const {
    return alive;
}

sf::Vector2f Player::getPosition() const {
    return sprite->getPosition();
}

sf::FloatRect Player::getBounds() const {
    return sprite->getGlobalBounds();
}

sf::Vector2f Player::getVelocity() const {
    return velocity;
}
