#pragma once

#include "entity.h"
#include "vector"

class Enemy
{

public:
    Entity entity;

    Enemy() 
    {
        this->entity = Entity("assets/PlayerRed_Frame_01_png_processed.png");
    }

    void DrawEnemy();
    void MovePosition(float x, float y);
    S2D_FRect GetRect();
};