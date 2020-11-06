#include "entity.h"

    Entity::Entity()
    {
        this->sprite = NULL;
        this->rect = {0};
        this->position = {0};
        this->center = {0};
        this->facing = {0};
    }

    // Parameterized Constructor
    Entity::Entity(const char *path)
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
        this->center.x = this->position.x + (rect.width / 2.0f);
        this->center.y = this->position.y + (rect.height / 2.0f);
        this->facing.x = this->position.x + (rect.width / 2.0f);
        this->facing.y = this->position.y + (rect.height / 2.0f) - 50;
    }

    void Entity::SetSprite(const char *path)
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
        this->center.x = this->position.x + (rect.width / 2.0f);
        this->center.y = this->position.y + (rect.height / 2.0f);
        this->facing.x = this->position.x + (rect.width / 2.0f);
        this->facing.y = this->position.y + (rect.height / 2.0f) - 50;

        this->sprite = sprite;
    }

    void Entity::Draw(bool debugMode)
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

    void Entity::SetSize(float width, float height)
    {
        this->sprite->width = width;
        this->sprite->height = height;
        this->rect.width = width;
        this->rect.height = height;
    }

    S2D_Vec2f Entity::GetPos()
    {
        return this->position;
    }

    void Entity::RotateSprite(float x, float y)
    {
        if (y > -0.16f && y < 0.01f && x > -0.16f && x < 0.01f)
            return;

        float angle_direction = atan2((this->center.y + y) - (this->center.y), (this->center.x - x) - (this->center.x));
        float angle_sprite = atan2((this->facing.y) - (this->center.y), (this->facing.x) - (this->center.x));
        angle_direction = angle_direction * 180 / M_PI;
        angle_sprite = angle_sprite * 180 / M_PI;
        float dif_angle = angle_sprite - angle_direction;

        S2D_RotateSprite(this->sprite, dif_angle, S2D_CENTER);
    }

    void Entity::Move(float x, float y)
    {
        this->sprite->x += x;
        this->sprite->y += y;
        this->position.x += x;
        this->position.y += y;
        this->rect.x += x;
        this->rect.y += y;
        this->center.x = this->position.x + (rect.width / 2.0f);
        this->center.y = this->position.y + (rect.height / 2.0f);
        this->facing.x = this->position.x + (rect.width / 2.0f);
        this->facing.y = this->position.y + (rect.height / 2.0f) - 50;
    }

    void Entity::SetPosition(float x, float y)
    {
        this->sprite->x = x;
        this->sprite->y = y;
        this->position.x = x;
        this->position.y = y;
        this->rect.x = x;
        this->rect.y = y;
        this->center.x = x + (rect.width / 2.0f);
        this->center.y = y + (rect.height / 2.0f);
        this->facing.x = x + (rect.width / 2.0f);
        this->facing.y = y + (rect.height / 2.0f) - 50;
    }

    S2D_FRect Entity::GetRect()
    {
        return this->rect;
    }