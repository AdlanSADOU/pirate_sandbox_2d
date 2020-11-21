#include "ammunition.h"
#include "enemy.h"
#include "math.h"

extern float xAxis, yAxis;
extern bool up, down, left, right, shift;

AmmunitionType *Projectiles::CreateAmmo(Entity *entity, const char *path)
{
    AmmunitionType *ammo = (AmmunitionType *)malloc(sizeof(AmmunitionType));
    ammo->speed = 5.0f + sqrt((xAxis * xAxis) + (yAxis * yAxis));
    ammo->direction = sf::Vector2f(cos(entity->angle * M_PI / 180), sin(entity->angle * M_PI / 180));
    ammo->entity = new Entity(path);
    ammo->entity->SetPosition(entity->facing);
    ammo->entity->sprite->setRotation(entity->angle +90);
    ammo->dmg = 50;
    ammo->destroyed = 0;
    ammo->clock.restart();
    ammo->lifeClock.restart();

    return (ammo);
}

Entity *ent;
void Projectiles::PlayerShoot(Entity *entity, const char *ammoSpritePath)
{
    sf::Time shootingTime = ROFClock.getElapsedTime();

    if (shootingTime.asSeconds() > ROF_GREEN_LASER) {
        ent = entity;
        Ammunitions.push_back(CreateAmmo(entity, ammoSpritePath));
        ROFClock.restart();
    }
}

void Projectiles::UpdatePosition(AmmunitionType *ammo)
{
    sf::Time time = ammo->clock.getElapsedTime();

    if (time.asSeconds() > 0.01f) {
        ammo->entity->Move(ammo->direction.x * ammo->speed, ammo->direction.y * ammo->speed);
        ammo->clock.restart();
    }
}

void Projectiles::FreeShoot(AmmunitionType *ammo, int index)
{
    ammo->entity->FreeEntity();
    free(ammo);
    Ammunitions.erase(Ammunitions.begin() + index);
}

void Projectiles::CheckIfHit(AmmunitionType *ammo, int index)
{
    std::vector<EnnemyType *> Ennemies = GetEnnemies();

    sf::FloatRect ammoRect = ammo->entity->sprite->getGlobalBounds();

    for (int i = 0; i < Ennemies.size(); i++) {
        //Do not check if dead
        if (Ennemies[i]->dead != 0) continue;

        sf::FloatRect ennemyRect = Ennemies[i]->entity->sprite->getGlobalBounds();

        //Check if intersects
        if (ennemyRect.intersects(ammoRect) && Projectiles::ownedByPlayer) {
            ammo->destroyed = 1;
            Ennemies[i]->hp -= ammo->dmg;
            if (Ennemies[i]->hp <= 0) {
                Ennemies[i]->dead = 1;
                Ennemies[i]->explosionClock.restart();
                Ennemies[i]->lifeClock.restart();
            }
        }
    }
}

void Projectiles::UpdateShoot(AmmunitionType *ammo, int index)
{
    UpdatePosition(ammo);
    CheckIfHit(ammo, index);

    sf::Time ammoLifeTime = ammo->lifeClock.getElapsedTime();

    if (Ammunitions.size() > 0) {
        if (ammoLifeTime.asSeconds() > 3.0f || ammo->destroyed == 1) {
            FreeShoot(ammo, index);
            return;
        }
    }
}

void Projectiles::RenderShoot(sf::RenderWindow &window) // must take window as parameter
{
    for (int i = 0; i < Ammunitions.size(); i++) {
        window.draw(*Ammunitions[i]->entity->sprite);
        UpdateShoot(Ammunitions[i], i);
    }
}
