#pragma once

#include "game.h"
#include "vector"

struct Ammunition {
    Entity *sprite;
    S2D_FRect rect;
    S2D_Vec2f position;
    S2D_Sound sound;
}fion;

void playerShoot(void);
void renderShoot(void);