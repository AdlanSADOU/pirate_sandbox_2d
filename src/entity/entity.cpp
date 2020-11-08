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
        this->position = this->sprite->getPosition();
        this->sprite->setOrigin(this->rect.width / 2, this->rect.height / 2);
        
        this->center.x = this->position.x + (rect.width / 2.0f);
        this->center.y = this->position.y + (rect.height / 2.0f);
        this->facing.x = this->position.x + (rect.width / 2.0f);
        this->facing.y = this->position.y + (rect.height / 2.0f) - 50;
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
        this->position = this->sprite->getPosition();
        this->sprite->setOrigin(this->rect.width / 2, this->rect.height / 2);

        this->center.x = this->position.x + (rect.width / 2.0f);
        this->center.y = this->position.y + (rect.height / 2.0f);
        this->facing.x = this->position.x + (rect.width / 2.0f);
        this->facing.y = this->position.y + (rect.height / 2.0f) - 50;

        this->sprite = sprite;
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

        this->sprite->setRotation(dif_angle);
    }

    void Entity::Move(float x, float y)
    {
        
        this->sprite->move(sf::Vector2f(x, y));


        this->center.x = this->position.x + (rect.width / 2.0f);
        this->center.y = this->position.y + (rect.height / 2.0f);
        this->facing.x = this->position.x + (rect.width / 2.0f);
        this->facing.y = this->position.y + (rect.height / 2.0f) - 50;
    }

    void Entity::SetPosition(sf::Vector2f pos)
    {
        this->sprite->setPosition(pos);

        this->position.x = pos.x;
        this->position.y = pos.y;

        this->center.x = pos.x + (rect.width / 2.0f);
        this->center.y = pos.y + (rect.height / 2.0f);
        this->facing.x = pos.x + (rect.width / 2.0f);
        this->facing.y = pos.y + (rect.height / 2.0f) - 50;
    }

    sf::Vector2f Entity::GetPos()
    {
        return this->sprite->getPosition();
    }

    sf::FloatRect Entity::GetRect()
    {
        return (sf::FloatRect)this->sprite->getGlobalBounds();
    }