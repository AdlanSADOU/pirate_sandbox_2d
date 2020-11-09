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
        this->facing.y = this->position.y + 30;

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
        this->facing.y = this->position.y + 30;

        this->sprite = sprite;
        this->angle = 0;
    }

    void Entity::RotateSprite(float x, float y)
    {
        if (y > -0.16f && y < 0.01f && x > -0.16f && x < 0.01f)
            return;

        float angle_direction = atan2((this->position.y + y) - (this->position.y), (this->position.x - x) - (this->position.x));
        float angle_sprite = atan2((this->facing.y) - (this->position.y), (this->facing.x) - (this->position.x));
        angle_direction = angle_direction * 180 / M_PI;
        angle_sprite = angle_sprite * 180 / M_PI;
        float dif_angle = angle_sprite - angle_direction + 180;

        printf("%f\n", dif_angle);
        this->sprite->setRotation(dif_angle);
    }

    void Entity::Move(float x, float y)
    {
        //return;
        this->sprite->move(sf::Vector2f(x, y));
        this->position = this->GetPos();

        this->facing.x = this->position.x;
        this->facing.y = this->position.y + 30;
    }

    void Entity::SetPosition(sf::Vector2f pos)
    {
        this->sprite->setPosition(pos);
        this->position = this->GetPos();

        this->facing.x = pos.x;
        this->facing.y = pos.y + 30;
    }

    sf::Vector2f Entity::GetDirection()
    {
        return (sf::Vector2f(0, 0)); //TODO : return the futur direction.
    }

    sf::Vector2f Entity::GetPos()
    {
        return this->sprite->getPosition();
    }

    sf::FloatRect Entity::GetRect()
    {
        return (sf::FloatRect)this->sprite->getGlobalBounds();
    }