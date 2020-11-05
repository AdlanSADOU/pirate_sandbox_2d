#if !defined(GAME_H)
#define GAME_H

#include "simple2d.h"

extern S2D_Window *window;


extern float xAxis;
extern float yAxis;

typedef struct
{
    S2D_Sprite *sprite;
    S2D_FRect rect;
    S2D_Vec2f position;
    S2D_Vec2f center;
} sdEntity;

// class implementation of sdEntity
class Entity
{
    S2D_Sprite *sprite;
    S2D_FRect rect;
    S2D_Vec2f position;
    S2D_Vec2f center;
    S2D_Vec2f facing;
    /*
    Abstraction over S2D_Sprite
    do not attempt to modify sprite pointer directly. The values will not be reflected in S2D_IRect and S2D_vec2i
    */
public:

    // Default Constructor
    Entity()
    {
        this->sprite = NULL;
        this->rect = {0};
        this->position = {0};
        this->center = {0};
        this->facing = {0};
    }

    // Parameterized Constructor
    Entity(const char *path)
    {
        this->sprite = S2D_CreateSprite(path);
        if (!sprite)
        {
            printf("Sprite creation failed %d %s", __LINE__, __FILE__);
            return;
        }

        this->rect.height = sprite->height;
        this->rect.width = sprite->width;
        this->rect.x = sprite->x;
        this->rect.y = sprite->y;

        this->position.x = sprite->x;
        this->position.y = sprite->y;
        this->center.x = this->position.x + (rect.width / 2.0);
        this->center.y = this->position.y + (rect.height / 2.0);
        this->facing.x = this->position.x + (rect.width / 2.0);
        this->facing.y = this->position.y + (rect.height / 2.0) - 50;
    }

    void SetSprite(const char *path)
    {
        if (this->sprite)
        {
            S2D_FreeSprite(this->sprite);
            this->sprite = NULL;
        }

        this->sprite = NULL;
        this->sprite = S2D_CreateSprite(path);
        if (!sprite)
        {
            printf("Sprite creation failed %d %s", __LINE__, __FILE__);
            return;
        }

        this->rect.height = sprite->height;
        this->rect.width = sprite->width;
        this->rect.x = sprite->x;
        this->rect.y = sprite->y;

        this->position.x = sprite->x;
        this->position.y = sprite->y;
        this->center.x = this->position.x + (rect.width / 2.0);
        this->center.y = this->position.y + (rect.height / 2.0);
        this->facing.x = this->position.x + (rect.width / 2.0);
        this->facing.y = this->position.y + (rect.height / 2.0) - 50;

        this->sprite = sprite;
    }

    void Draw(bool debugMode)
    {
        S2D_FRect rect = this->rect;

        GLfloat x1 = rect.x, y1 = rect.y;
        GLfloat x2 = rect.x + rect.width, y2 = rect.y;
        GLfloat x3 = rect.x + rect.width, y3 = rect.y + rect.height;
        GLfloat x4 = rect.x, y4 = rect.y + rect.height;

        S2D_Color color = {1.0f, 0.5f, 0.5f, 1.0f};

        if (debugMode)
            S2D_DrawRect(rect, color, true);

        S2D_DrawSprite(this->sprite);
    }

    void SetSize(float width, float height)
    {
        this->sprite->width = width;
        this->sprite->height = height;
        this->rect.width = width;
        this->rect.height = height;
    }

    S2D_Vec2f GetPos()
    {
        return this->position;
    }

    void RotateSprite(float x, float y)
    {
        if (y > -0.16 && y < 0.01 && x > -0.16 && x < 0.01)
            return;
        float angle_direction = atan2((this->center.y + y) - (this->center.y),
            (this->center.x - x) - (this->center.x));
        float angle_sprite = atan2((this->facing.y) - (this->center.y),
            (this->facing.x) - (this->center.x));
        angle_direction = angle_direction * 180 / M_PI;
        angle_sprite = angle_sprite * 180 / M_PI;
        if (angle_direction < 0) angle_direction = 360 + angle_direction;
        if (angle_sprite < 0) angle_sprite = 360 + angle_sprite;
        float dif_angle = angle_sprite - angle_direction;
        S2D_RotateSprite(this->sprite, dif_angle, S2D_CENTER);
    }

    void Move(float x, float y)
    {
        this->sprite->x += x;
        this->sprite->y += y;
        this->position.x += x;
        this->position.y += y;
        this->rect.x += x;
        this->rect.y += y;
        this->center.x = this->position.x + (rect.width / 2.0);
        this->center.y = this->position.y + (rect.height / 2.0);
        this->facing.x = this->position.x + (rect.width / 2.0);
        this->facing.y = this->position.y + (rect.height / 2.0) - 50;
    }

    void SetPosition(float x, float y)
    {
        this->sprite->x = x;
        this->sprite->y = y;
        this->position.x = x;
        this->position.y = y;
        this->rect.x = x;
        this->rect.y = y;
        this->center.x = x + (rect.width / 2.0);
        this->center.y = y + (rect.height / 2.0);
        this->facing.x = x + (rect.width / 2.0);
        this->facing.y = y + (rect.height / 2.0) - 50;
    }

    S2D_FRect GetRect()
    {
        return this->rect;
    }
};


typedef struct args
{
    char *str;
    int i;
} update_args;

// sdEntity
sdEntity *sdEntityCreate(const char *path);
void sdEntityDraw(sdEntity *entity, bool debugMode);
void sdEntitySetSize(sdEntity *entity, float width, float height);
void sdEntityMove(sdEntity *entity, float x, float y);
void sdEntitySetPosition(sdEntity *entity, float x, float y);

// Game
void gameInit();
void gameUpdate(update_args *args);
void gameRender();
void gameInput(S2D_Event e);

#endif // GAME_H
