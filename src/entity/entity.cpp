#include "entity.h"

    Entity::Entity()
    {}

    // Parameterized Constructor
    Entity::Entity(const char *path)
    {
        this->texture = new sf::Texture();
        if (!this->texture->loadFromFile(path))
        {
            printf("Sprite creation failed %d %s", __LINE__, __FILE__);
            return;
        }
        this->sprite = new sf::Sprite(*this->texture);

        this->rect = this->sprite->getTextureRect();
        this->sprite->setOrigin(this->rect.width / 2, this->rect.height / 2);
        this->position = this->sprite->getPosition();

        this->facing.x = this->position.x;
        this->facing.y = this->position.y - 100;
        this->behind.x = this->position.x;
        this->behind.y = this->position.y + 25;

        this->angle = 0;
    }

    void Entity::SetSprite(const char *path)
    {
         this->texture = new sf::Texture();
        if (!this->texture->loadFromFile(path))
        {
            printf("Sprite creation failed %d %s", __LINE__, __FILE__);
            return;
        }
        this->sprite = new sf::Sprite(*this->texture);

        this->rect = this->sprite->getTextureRect();
        this->sprite->setOrigin(this->rect.width / 2, this->rect.height / 2);
        this->position = this->sprite->getPosition();

        this->facing.x = this->position.x;
        this->facing.y = this->position.y - 100;
        this->behind.x = this->position.x;
        this->behind.y = this->position.y + 25;

        this->sprite = sprite;
        this->angle = 0;
    }

    void Entity::FreeEntity()
    {
        free(this->sprite);
        free(this->texture);
        free(this);
    }

    void Entity::RotateSprite(float x, float y, int offset)
    {
        float angle_direction = atan2((this->position.y - y) - (this->position.y), (this->position.x - x) - (this->position.x));
        float save_angle = angle_direction * 180 / M_PI;
        angle_direction = angle_direction * 180 / M_PI - offset;

        float s = sin(angle_direction * M_PI / 180);
        float c = cos(angle_direction * M_PI / 180);
        // translate point back to origin:
        this->facing.x -= this->position.x;
        this->facing.y -= this->position.y;
        this->behind.x -= this->position.x;
        this->behind.y -= this->position.y;
        // rotate point
        float xnew1 = this->facing.x * c - this->facing.y * s;
        float ynew1 = this->facing.x * s + this->facing.y * c;
        float xnew2 = this->behind.x * c - this->behind.y * s;
        float ynew2 = this->behind.x * s + this->behind.y * c;
        // translate point back:
        this->facing.x = xnew1 + this->position.x;
        this->facing.y = ynew1 + this->position.y;
        this->behind.x = xnew2 + this->position.x;
        this->behind.y = ynew2 + this->position.y;
    
        this->angle = save_angle + 180;
        this->sprite->setRotation(angle_direction);
    }

    void Entity::Move(float x, float y)
    {
        //return;
        this->sprite->move(sf::Vector2f(x, y));
        this->position = this->GetPos();

        this->facing.x = this->position.x;
        this->facing.y = this->position.y - 100;
        this->behind.x = this->position.x;
        this->behind.y = this->position.y + 25;
    }

    void Entity::SetPosition(sf::Vector2f pos)
    {
        this->sprite->setPosition(pos);
        this->position = this->GetPos();

        this->facing.x = this->position.x;
        this->facing.y = this->position.y - 100;
        this->behind.x = this->position.x;
        this->behind.y = this->position.y + 25;
    }

    sf::Vector2f Entity::GetDirection()
    {
        return (this->facing);
    }

    sf::Vector2f Entity::GetPos()
    {
        return this->sprite->getPosition();
    }

    sf::FloatRect Entity::GetRect()
    {
        return (sf::FloatRect)this->sprite->getGlobalBounds();
    }