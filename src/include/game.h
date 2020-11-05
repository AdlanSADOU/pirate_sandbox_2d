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
} sdEntity;

// class implementation of sdEntity
class Entity
{
    S2D_Sprite *sprite;
    S2D_FRect rect;
    S2D_Vec2f position;
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

    void Move(float x, float y)
    {
        this->sprite->x += x;
        this->sprite->y += y;
        this->position.x += x;
        this->position.y += y;
        this->rect.x += x;
        this->rect.y += y;
    }

    void SetPosition(float x, float y)
    {
        this->sprite->x = x;
        this->sprite->y = y;
        this->position.x = x;
        this->position.y = y;
        this->rect.x = x;
        this->rect.y = y;
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
