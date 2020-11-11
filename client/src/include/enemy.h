#pragma once

#include "game.h"

typedef struct {
    Entity *entity;
    Entity *explosion;
    sf::IntRect explosionRect;
    sf::FloatRect rect;
    sf::Vector2f direction;
    sf::Clock clock;
    sf::Clock lifeClock;
    sf::Clock explosionClock;
    sf::Sound sound;
    int hp;
    int dead;
    float speed;
} EnnemyType;

std::vector<EnnemyType *> GetEnnemies(void);
void CreateEnemy(void);
void RenderEnnemies(void);
sf::Vector2f GetRandomNormalizedVector();
