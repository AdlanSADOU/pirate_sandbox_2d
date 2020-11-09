#include "ammunition.h"

std::vector<AmmunitionType *> Ammunitions;
sf::Clock ROFClock;

AmmunitionType *CreateAmmo()
{
    Entity *playerClass = getPlayer();

    AmmunitionType *ammo = (AmmunitionType *)malloc(sizeof(AmmunitionType));
    ammo->speed = 5.0f + sqrt((xAxis * xAxis) + (yAxis * yAxis));
    ammo->direction = sf::Vector2f(cos(playerClass->angle * M_PI / 180), sin(playerClass->angle * M_PI / 180));
    ammo->entity = new Entity("assets/256px/Laser_Large_png_processed.png");
    ammo->entity->SetPosition(playerClass->GetPos());
    ammo->position = playerClass->GetPos();
    ammo->clock.restart();
    ammo->lifeClock.restart();

    return (ammo);
}

void playerShoot()
{
    sf::Time shootingTime = ROFClock.getElapsedTime();

    if (shootingTime.asSeconds() > ROF_GREEN_LASER) {
        Ammunitions.push_back(CreateAmmo());
        ROFClock.restart();
    }
    // Ammunitions.push_back(CreateAmmo());
    
}

void UpdatePosition(AmmunitionType *ammo)
{
    sf::Time time = ammo->clock.getElapsedTime();

    if (time.asSeconds() > 0.01f) {
        ammo->entity->RotateSprite(ammo->direction.x, ammo->direction.y, 90);
        ammo->entity->Move(ammo->direction.x * ammo->speed, ammo->direction.y * ammo->speed);
        ammo->clock.restart();
    }
}

void FreeShoot(AmmunitionType *ammo, int index)
{
    sf::Time ammoLifeTime = ammo->lifeClock.getElapsedTime();
    if (ammoLifeTime.asSeconds() > 3.0f) {
        ammo->entity->FreeEntity();
        Ammunitions.erase(Ammunitions.begin() + index);
    }
}

void UpdateShoot(AmmunitionType *ammo, int index)
{
    UpdatePosition(ammo);
    if (Ammunitions.size() > 0)
        FreeShoot(ammo, index);
}

void RenderShoot()
{
    for (int i = 0; i < Ammunitions.size(); i++) {
        gWindow->draw(*Ammunitions[i]->entity->sprite);
        UpdateShoot(Ammunitions[i], i);
    }
}
