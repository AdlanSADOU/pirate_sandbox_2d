#include "ammunition.h"
#include "stdlib.h"

std::vector<Ammunition *> Ammunitions;

Ammunition *create_ammo()
{
    Entity *playerClass = getPlayer();

    Ammunition *ammo = (Ammunition *)malloc(sizeof(Ammunition));

    ammo->sprite = new Entity("assets/256px/Laser_Large_png_processed.png");
    ammo->sprite->SetPosition(playerClass->GetPos());
    ammo->position = playerClass->GetPos();

    return (ammo);
}

void playerShoot()
{
    Ammunitions.push_back(create_ammo());
    printf("zae\n");
}

void renderShoot()
{
    for (int i = 0; i < Ammunitions.size(); i++) {
        Ammunitions[i]->sprite->Draw(false);
    }
}