#include "ammunition.h"

std::vector<Ammunition *> Ammunitions;

Ammunition *create_ammo()
{
    Entity *playerClass = getPlayer();

    Ammunition *ammo = (Ammunition *)malloc(sizeof(Ammunition));

    ammo->entity = new Entity("assets/256px/Laser_Large_png_processed.png");
    ammo->entity->SetPosition(playerClass->GetPos());
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
        gWindow->draw(*Ammunitions[i]->entity->sprite);
    }
}
