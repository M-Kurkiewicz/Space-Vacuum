#include "Asteroid.h"
#include <iostream>

Asteroid::Asteroid(TextureManager& textureManager, sf::Vector2f position, sf::Vector2f velocity_val)
    : velocity(velocity_val) {
    try {
        sprite.setTexture(textureManager.get("asteroid"));
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error loading asteroid texture: " << e.what() << std::endl;
    }
    sprite.setPosition(position);
    sprite.setScale(0.2f, 0.2f); // Rozmiar asteroidy
}

void Asteroid::update(float dt) {
    if (active) {
        sprite.move(velocity * dt);
        sf::Vector2f pos = sprite.getPosition();
        sf::FloatRect bounds = sprite.getGlobalBounds();
        if (pos.x + bounds.width < 0 || pos.x > SCREEN_WIDTH ||
            pos.y + bounds.height < 0 || pos.y > SCREEN_HEIGHT) {
            active = false;
        }
    }
}

void Asteroid::draw(sf::RenderWindow& window) {
    if (active) {
        window.draw(sprite);
    }
}