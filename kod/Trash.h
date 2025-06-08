#ifndef TRASH_H
#define TRASH_H

#include "Entity.h"
#include "Defines.h"
#include "ResourceManager.h"

class Trash : public Entity {
public:
    Trash(TextureManager& textureManager, sf::Vector2f position);
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

    int getValue() const;

private:
    int value; // Punkty
};

#endif // TRASH_H