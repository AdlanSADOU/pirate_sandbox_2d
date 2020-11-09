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

    return (ammo);
}

void playerShoot()
{
    sf::Time shootingTime = ROFClock.getElapsedTime();

    if (shootingTime.asSeconds() > ROF_GREEN_LASER) {
        Ammunitions.push_back(CreateAmmo());
        ROFClock.restart();
    }
}

void UpdatePosition(AmmunitionType *ammo)
{
    sf::Time time = ammo->clock.getElapsedTime();

    if (time.asSeconds() > 0.01f) {
        ammo->entity->RotateSprite(ammo->direction.x, ammo->direction.y);
        ammo->entity->Move(ammo->direction.x * ammo->speed, ammo->direction.y * ammo->speed);
        ammo->clock.restart();
    }
}

void UpdateShoot(AmmunitionType *ammo)
{
    UpdatePosition(ammo);
}

void RenderShoot()
{
    for (int i = 0; i < Ammunitions.size(); i++) {
        UpdateShoot(Ammunitions[i]);
        gWindow->draw(*Ammunitions[i]->entity->sprite);
    }
}
