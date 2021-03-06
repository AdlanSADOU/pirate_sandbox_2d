#pragma once

#include "entity.h"
#include "particles.h"
#include "ammunition.h"

#include "imgui-common.h"

typedef struct {
    ParticleSystem *particleSystem;
    Projectiles *projectile;
    Entity *entity;
    Entity *explosion;
    sf::IntRect explosionRect;
    sf::FloatRect rect;
    sf::Vector2f direction;
    sf::Clock clock;
    sf::Clock lifeClock;
    sf::Clock explosionClock;
    sf::Sound sound;
    sf::RectangleShape shieldRect;
    sf::RectangleShape hpRect;
    int hp;
    int dead;
    int shield;
    float speed;
} EnnemyType;

std::vector<EnnemyType *> GetEnnemies(void);
void CreateEnemy(void);
void RenderEnnemies(sf::RenderWindow &window);
