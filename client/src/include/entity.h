#pragma once

// #include "simple2d.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#ifndef M_PI
#define M_PI    3.14159265358979323846264338327950288   /**< pi */
#endif

// class implementation of sdEntity
class Entity
{
private:

    // S2D_Sprite *sprite;
    // S2D_FRect rect;
    // S2D_Vec2f position;
    // S2D_Vec2f center;
    // S2D_Vec2f facing;
public:
    sf::Texture *texture;
    sf::Sprite *sprite;
    sf::IntRect rect;
    sf::Vector2f position;
    sf::Vector2f facing;
    sf::Vector2f behind;
    sf::Vector2f behind_far;
    bool up = false, down = false, left = false, right = false, shift = false;
    float angle;


    // Default Constructor
    Entity();
    // Parameterized Constructor
    Entity(const char *path);

    void SetClipRectangle(int x, int y, int width, int height);
    void SetSize(float width, float height);
    void RotateSprite(float x, float y, int offset);
    void SetPosition(sf::Vector2f pos);
    void SetSprite(const char *path);
    void FreeEntity(void);
    void Move(float x, float y);

    sf::Vector2f GetPos(void);
    sf::Vector2f GetDirection(void);
    sf::FloatRect GetRect();
};

sf::Vector2f RotatePointAroundCenter(sf::Vector2f point, sf::Vector2f center, float angle_rad);