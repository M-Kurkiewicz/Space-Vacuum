#include "Player.h"
#include <iostream> // For debug

Player::Player(TextureManager& textureManager) : lives(INITIAL_LIVES) {
    try {
        sprite.setTexture(textureManager.get("player"));
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error loading player texture: " << e.what() << std::endl;
    }
    resetPosition(); // Tutaj ustawiany jest m.in. origin sprite'a na jego �rodek
    sprite.setRotation(0.f); // Ustawienie pocz�tkowej rotacji na 0 stopni (do g�ry)
}

void Player::update(float dt) {
    handleInput(); // Najpierw obs�uga inputu i ustawienie rotacji/pr�dko�ci
    sprite.move(velocity * dt); // Potem ruch

    sf::Vector2f pos = sprite.getPosition();
    sf::FloatRect bounds = sprite.getGlobalBounds(); // GlobalBounds uwzgl�dnia rotacj� i skal�

    float effectiveWidth = bounds.width;
    float effectiveHeight = bounds.height;

    if (sprite.getPosition().x - effectiveWidth / 2.f < 0) {
        pos.x = effectiveWidth / 2.f;
    }
    if (sprite.getPosition().y - effectiveHeight / 2.f < 0) {
        pos.y = effectiveHeight / 2.f;
    }
    if (sprite.getPosition().x + effectiveWidth / 2.f > SCREEN_WIDTH) {
        pos.x = SCREEN_WIDTH - effectiveWidth / 2.f;
    }
    if (sprite.getPosition().y + effectiveHeight / 2.f > SCREEN_HEIGHT) {
        pos.y = SCREEN_HEIGHT - effectiveHeight / 2.f;
    }
    sprite.setPosition(pos);
}

void Player::draw(sf::RenderWindow& window) {
    if (active) {
        window.draw(sprite);
    }
}

void Player::handleInput() {
    velocity = sf::Vector2f(0.f, 0.f);

    // Okre�l pr�dko�� na podstawie wci�ni�tych klawiszy
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocity.x = -PLAYER_SPEED;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocity.x = PLAYER_SPEED;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        velocity.y = -PLAYER_SPEED;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        velocity.y = PLAYER_SPEED;
    }

    if (velocity.x < 0) {
        sprite.setRotation(270.f); // Obr�t o -90 stopni (lub 270) od pozycji "do g�ry"
    }
    else if (velocity.x > 0) {
        sprite.setRotation(90.f);  // Obr�t o +90 stopni od pozycji "do g�ry"
    }
    else {
        if (velocity.y < 0) { // Ruch w g�r�
            sprite.setRotation(0.f);   // Orientacja "do g�ry"
        }
        else if (velocity.y > 0) { // Ruch w d�
            sprite.setRotation(180.f); // Orientacja "do do�u"
        }
    }
}

void Player::resetPosition() {
    sf::FloatRect bounds = sprite.getLocalBounds(); // U�ywamy localBounds do centrowania origin
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f); // Kluczowe dla poprawnej rotacji wok� �rodka
    sprite.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - bounds.height * 1.5f); // Pozycja startowa (troch� wy�ej)
    sprite.setRotation(0.f); // Upewnij si�, �e na starcie jest obr�cony do g�ry
}

int Player::getLives() const {
    return lives;
}

void Player::loseLife() {
    if (lives > 0) {
        lives--;
    }
}

void Player::resetLives() {
    lives = INITIAL_LIVES;
}