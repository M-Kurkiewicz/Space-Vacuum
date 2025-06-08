#include "Trash.h"
#include <iostream>

Trash::Trash(TextureManager& textureManager, sf::Vector2f position) : value(10) {
    try {
        sprite.setTexture(textureManager.get("trash"));
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error loading trash texture: " << e.what() << std::endl;
    }
    sprite.setPosition(position);
    sprite.setScale(1.0f, 1.0f);
}

void Trash::update(float dt) {
    if (active) {
        sprite.move(0.f, BASE_TRASH_SPEED * dt);
        if (sprite.getPosition().y > SCREEN_HEIGHT) {
            active = false;
        }
    }
}

void Trash::draw(sf::RenderWindow& window) {
    if (active) {
        window.draw(sprite);
    }
}

int Trash::getValue() const {
    return value;
}