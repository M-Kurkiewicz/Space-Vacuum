#include "Player.h"
#include <iostream> // For debug

Player::Player(TextureManager& textureManager) : lives(INITIAL_LIVES) {
    try {
        sprite.setTexture(textureManager.get("player"));
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error loading player texture: " << e.what() << std::endl;
    }
    resetPosition(); // Tutaj ustawiany jest m.in. origin sprite'a na jego œrodek
    sprite.setRotation(0.f); // Ustawienie pocz¹tkowej rotacji na 0 stopni (do góry)
}

void Player::update(float dt) {
    handleInput(); // Najpierw obs³uga inputu i ustawienie rotacji/prêdkoœci
    sprite.move(velocity * dt); // Potem ruch

    sf::Vector2f pos = sprite.getPosition();
    sf::FloatRect bounds = sprite.getGlobalBounds(); // GlobalBounds uwzglêdnia rotacjê i skalê

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

    // Okreœl prêdkoœæ na podstawie wciœniêtych klawiszy
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
        sprite.setRotation(270.f); // Obrót o -90 stopni (lub 270) od pozycji "do góry"
    }
    else if (velocity.x > 0) {
        sprite.setRotation(90.f);  // Obrót o +90 stopni od pozycji "do góry"
    }
    else {
        if (velocity.y < 0) { // Ruch w górê
            sprite.setRotation(0.f);   // Orientacja "do góry"
        }
        else if (velocity.y > 0) { // Ruch w dó³
            sprite.setRotation(180.f); // Orientacja "do do³u"
        }
    }
}

void Player::resetPosition() {
    sf::FloatRect bounds = sprite.getLocalBounds(); // U¿ywamy localBounds do centrowania origin
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f); // Kluczowe dla poprawnej rotacji wokó³ œrodka
    sprite.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - bounds.height * 1.5f); // Pozycja startowa (trochê wy¿ej)
    sprite.setRotation(0.f); // Upewnij siê, ¿e na starcie jest obrócony do góry
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