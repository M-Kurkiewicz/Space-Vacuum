#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Defines.h"
#include "ResourceManager.h"

class Player : public Entity {
public:
    Player(TextureManager& textureManager);
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

    void handleInput();
    void resetPosition();

    int getLives() const;
    void loseLife();
    void resetLives();

private:
    sf::Vector2f velocity;
    int lives;
};

#endif // PLAYER_H