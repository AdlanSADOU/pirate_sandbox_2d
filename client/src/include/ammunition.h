// Ammunition.h

#pragma once

// #include "game.h"
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "entity.h"

#define ROF_GREEN_LASER (0.15)

typedef struct {
    Entity *entity;
    sf::FloatRect rect;
    sf::Sound sound;
    sf::Vector2f direction;
    sf::Clock clock;
    sf::Clock lifeClock;
    float speed;
    int destroyed;
    int dmg;
} AmmunitionType;

class Projectiles
{
    sf::Clock ROFClock;

    AmmunitionType *CreateAmmo(Entity *entity);
    void UpdatePosition(AmmunitionType *ammo);
    void FreeShoot(AmmunitionType *ammo, int index);
    void CheckIfHit(AmmunitionType *ammo, int index);
    void UpdateShoot(AmmunitionType *ammo, int index);

public:
    std::vector<AmmunitionType *> Ammunitions;
    
    void PlayerShoot(Entity *entity);
    void RenderShoot(sf::RenderWindow &window);

};