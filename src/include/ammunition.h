// Ammunition.h

#pragma once

#include "game.h"

typedef struct {
    Entity *entity;
    sf::FloatRect rect;
    sf::Vector2f position;
    sf::Sound sound;
} Ammunition;

Entity *getPlayer(void);
void playerShoot(void);
void renderShoot(void);