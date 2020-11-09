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
        this->facing.y = this->position.y - 30;
        this->behind.x = this->position.x;
        this->behind.y = this->position.y + 30;

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
        this->facing.y = this->position.y - 30;
        this->behind.x = this->position.x;
        this->behind.y = this->position.y + 30;

        this->sprite = sprite;
        this->angle = 0;
    }

    void Entity::RotateSprite(float x, float y)
    {
        if (y > -0.16f && y < 0.01f && x > -0.16f && x < 0.01f)
            return;

        float angle_direction = atan2((this->position.y - y) - (this->position.y), (this->position.x - x) - (this->position.x));
        angle_direction = angle_direction * 180 / M_PI - 90;

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
    
        this->angle = angle_direction;
        this->sprite->setRotation(this->angle);
    }

    void Entity::Move(float x, float y)
    {
        //return;
        this->sprite->move(sf::Vector2f(x, y));
        this->position = this->GetPos();

        this->facing.x = this->position.x;
        this->facing.y = this->position.y - 30;
        this->behind.x = this->position.x;
        this->behind.y = this->position.y + 30;
    }

    void Entity::SetPosition(sf::Vector2f pos)
    {
        this->sprite->setPosition(pos);
        this->position = this->GetPos();

        this->facing.x = this->position.x;
        this->facing.y = this->position.y - 30;
        this->behind.x = this->position.x;
        this->behind.y = this->position.y + 30;
    }

    sf::Vector2f Entity::GetPos()
    {
        return this->sprite->getPosition();
    }

    sf::FloatRect Entity::GetRect()
    {
        return (sf::FloatRect)this->sprite->getGlobalBounds();
    }