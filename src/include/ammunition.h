// Ammunition.h

#pragma once

#include "game.h"

typedef struct {
    Entity *entity;
    sf::FloatRect rect;
    sf::Vector2f position;
    sf::Sound sound;
    sf::Vector2f direction;
    sf::Clock clock;
    float speed;
} Ammunition;

Entity *getPlayer(void);
void playerShoot(void);
void RenderShoot(void);