// game.h

#pragma once

#include "simple2d.h"
#include "entity.h"
#include "enemy.h"
#include "ammunition.h"

#include <vector>

extern S2D_Window *gWindow;

extern float xAxis;
extern float yAxis;

typedef struct
{
    S2D_Sprite *sprite;
    S2D_FRect rect;
    S2D_Vec2f position;
    S2D_Vec2f center;
} sdEntity;

typedef struct args
{
    char *str;
    int i;
} update_args;

// Game
void gameInit();
void gameUpdate(update_args *args);
void gameRender();
Entity *getPlayer(void);
void gameInput(S2D_Event e);
