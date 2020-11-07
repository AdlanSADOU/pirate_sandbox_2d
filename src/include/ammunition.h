#pragma once

#include "game.h"
#include "vector"

typedef struct Ammunition {
    S2D_Sprite *sprite;
    S2D_FRect rect;
    S2D_Vec2f position;
    S2D_Sound sound;
};

std::vector<Ammunition *> Ammunitions;