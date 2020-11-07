#pragma once

#include "simple2d.h"

// class implementation of sdEntity
class Entity
{
private:

    S2D_Sprite *sprite;
    S2D_FRect rect;
    S2D_Vec2f position;
    S2D_Vec2f center;
    S2D_Vec2f facing;
    
public:

    // Default Constructor
    Entity();
    // Parameterized Constructor
    Entity(const char *path);

    void SetClipRectangle(int x, int y, int width, int height);
    void SetSize(float width, float height);
    void RotateSprite(float x, float y);
    void SetPosition(float x, float y);
    void SetSprite(const char *path);
    void Move(float x, float y);
    void Draw(bool debugMode);

    S2D_Vec2f GetPos();
    S2D_FRect GetRect();
};