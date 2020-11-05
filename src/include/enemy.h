#pragma once

#include "game.h"
#include "vector"

class Enemy
{

    Entity *enemy = new Entity("assets/PlayerRed_Frame_01_png_processed.png");
public:
    Enemy() {};
    void DrawEnemy();
    void MovePosition(float x, float y);
};