// Ammunition.h

#pragma once

#include "game.h"

typedef struct {
    Entity *sprite;
    S2D_FRect rect;
    S2D_Vec2f position;
    S2D_Sound sound;
} Ammunition;

Entity *getPlayer(void);
void playerShoot(void);
void renderShoot(void);