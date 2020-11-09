// Ammunition.h

#pragma once

#include "game.h"

#define ROF_GREEN_LASER (0.15)

typedef struct {
    Entity *entity;
    sf::FloatRect rect;
    sf::Vector2f position;
    sf::Sound sound;
    sf::Vector2f direction;
    sf::Clock clock;
    sf::Clock lifeClock;
    float speed;
} AmmunitionType;

typedef struct {
    float speed;
} Gun;

Entity *getPlayer(void);
void playerShoot(void);
void RenderShoot(void);