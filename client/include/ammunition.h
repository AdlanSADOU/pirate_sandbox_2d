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

    AmmunitionType *CreateAmmo(Entity *entity, const char *path);
    void UpdatePosition(AmmunitionType *ammo);
    void FreeShoot(AmmunitionType *ammo, int index);
    void CheckIfHit(AmmunitionType *ammo, int index);
    void UpdateShoot(AmmunitionType *ammo, int index);
    std::vector<AmmunitionType *> Ammunitions;

public:
    bool ownedByPlayer;

    Projectiles() {
        this->ownedByPlayer = false;
    }
    
    void PlayerShoot(Entity *entity, const char *ammoSpritePath);
    void RenderShoot(sf::RenderWindow &window);

};