#include "entity.h"

    Entity::Entity()
    {}

    // Parameterized Constructor
    Entity::Entity(const char *path)
    {
        this->texture.loadFromFile(path);
        this->sprite = sf::Sprite(this->texture);
        // if (!sprite)
        // {
        //     printf("Sprite creation failed %d %s", __LINE__, __FILE__);
        //     return;
        // }

        this->rect = this->sprite.getTextureRect();
        this->position = this->sprite.getPosition();
        
        this->center.x = this->position.x + (rect.width / 2.0f);
        this->center.y = this->position.y + (rect.height / 2.0f);
        this->facing.x = this->position.x + (rect.width / 2.0f);
        this->facing.y = this->position.y + (rect.height / 2.0f) - 50;
    }

    void Entity::SetSprite(const char *path)
    {
        this->texture.loadFromFile(path);
        this->sprite = sf::Sprite(this->texture);
        // if (!sprite)
        // {
        //     printf("Sprite creation failed %d %s", __LINE__, __FILE__);
        //     return;
        // }

        this->rect = this->sprite.getTextureRect();
        this->position = this->sprite.getPosition();

        this->center.x = this->position.x + (rect.width / 2.0f);
        this->center.y = this->position.y + (rect.height / 2.0f);
        this->facing.x = this->position.x + (rect.width / 2.0f);
        this->facing.y = this->position.y + (rect.height / 2.0f) - 50;

        this->sprite = sprite;
    }

    void Entity::SetSize(float width, float height)
    {
        // this->sprite.set = width;
        // this->sprite->height = height;
        // this->rect.width = width;
        // this->rect.height = height;
    }

    // TODO(Lorentz): the rect needs to be rotated as well
    void Entity::RotateSprite(float x, float y)
    {
        if (y > -0.16f && y < 0.01f && x > -0.16f && x < 0.01f)
            return;

        float angle_direction = atan2((this->center.y + y) - (this->center.y), (this->center.x - x) - (this->center.x));
        float angle_sprite = atan2((this->facing.y) - (this->center.y), (this->facing.x) - (this->center.x));
        angle_direction = angle_direction * 180 / M_PI;
        angle_sprite = angle_sprite * 180 / M_PI;
        float dif_angle = angle_sprite - angle_direction;

        // S2D_RotateSprite(this->sprite, dif_angle, S2D_CENTER);
        this->sprite.rotate(dif_angle);
    }

    void Entity::Move(float x, float y)
    {
        
        this->sprite.move(sf::Vector2f(x, y));

        this->center.x = this->position.x + (rect.width / 2.0f);
        this->center.y = this->position.y + (rect.height / 2.0f);
        this->facing.x = this->position.x + (rect.width / 2.0f);
        this->facing.y = this->position.y + (rect.height / 2.0f) - 50;
    }

    void Entity::SetPosition(sf::Vector2f pos)
    {
        this->sprite.setPosition(pos);

        this->position.x = pos.x;
        this->position.y = pos.y;

        this->center.x = pos.x + (rect.width / 2.0f);
        this->center.y = pos.y + (rect.height / 2.0f);
        this->facing.x = pos.x + (rect.width / 2.0f);
        this->facing.y = pos.y + (rect.height / 2.0f) - 50;
    }

    /*
     * Set a region of the Sprite to be visible
     * if width or height extends the Sprite's width/height
     * the Sprite will be repeated
     */
    // void Entity::SetClipRectangle(int x, int y, int width, int height)
    // {
    //     S2D_ClipSprite(this->sprite, x, y, width, height);
    //     this->rect.height = height;
    //     this->rect.width = width;
    //     this->rect.x = this->sprite->x;
    //     this->rect.y = this->sprite->y;

    //     this->position.x = this->sprite->x;
    //     this->position.y = this->sprite->y;
    // }

    // S2D_Vec2f Entity::GetPos()
    // {
    //     return this->position;
    // }

    // S2D_FRect Entity::GetRect()
    // {
    //     return this->rect;
    // }