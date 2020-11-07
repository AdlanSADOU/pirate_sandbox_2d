#include "ammunition.h"

typedef struct Ammo {
    Entity *sprite;
    S2D_FRect rect;
    S2D_Vec2f position;
    S2D_Sound sound;
} Ammunition;

std::vector<Ammunition *> Ammunitions;

Ammunition *create_ammo()
{
    Ammunition *ammo = (Ammunition *)malloc(sizeof(Ammunition));
    Entity *playerClass = getPlayer();

    ammo->sprite->SetSprite("assets/256px/Laser_Large_png_processed.png");
    ammo->sprite->SetPosition(playerClass->GetPos());
    ammo->position = playerClass->GetPos();

    return (ammo);
}

void playerShoot()
{
    Ammunitions.push_back(create_ammo());
}

void renderShoot()
{
    for (int i = 0; i < Ammunitions.size(); i++) {
        Ammunitions[i]->sprite->Draw(false);
    }
}
