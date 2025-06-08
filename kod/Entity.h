#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
public:
    sf::Sprite sprite;
    bool active;

    Entity() : active(true) {}
    virtual ~Entity() = default; // Wa¿ny wirtualny destruktor dla polimorfizmu

    virtual void update(float dt) = 0; // Czysto wirtualna metoda
    virtual void draw(sf::RenderWindow& window) = 0; // Czysto wirtualna metoda

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }

    bool isActive() const {
        return active;
    }

    void setActive(bool status) {
        active = status;
    }
};

#endif // ENTITY_H