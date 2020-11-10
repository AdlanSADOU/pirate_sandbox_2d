#pragma once

#include "game.h"

typedef struct {
    Entity *entity;
    sf::FloatRect rect;
    sf::Vector2f position;
    sf::Sound sound;
    sf::Vector2f direction;
    sf::Clock clock;
    sf::Clock lifeClock;
    float speed;
} EnnemyType;

void PushEnemy(void);
void RenderEnnemies(void);
