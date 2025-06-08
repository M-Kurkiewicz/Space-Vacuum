#ifndef ASTEROID_H
#define ASTEROID_H

#include "Entity.h"
#include "Defines.h"
#include "ResourceManager.h"

class Asteroid : public Entity {
public:
    Asteroid(TextureManager& textureManager, sf::Vector2f position, sf::Vector2f velocity);
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::Vector2f velocity;
};

#endif // ASTEROID_H