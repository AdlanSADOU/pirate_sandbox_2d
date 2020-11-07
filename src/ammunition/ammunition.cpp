#include "ammunition.h"

Ammunition *create_ammo()
{
    Ammunition *ammo = (Ammunition *)malloc(sizeof(Ammunition));

    ammo->sprite = S2D_CreateSprite("assets/PixelBackgroundSeamlessVertically.png");
}
