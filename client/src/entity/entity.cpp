#include "entity.h"

int behind_offset = 25;
int behind_far_offset = 200;
int facing_offset = 100;

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

        this->sprite->setOrigin(this->sprite->getGlobalBounds().width / 2, this->sprite->getGlobalBounds().height / 2);
        this->position = this->sprite->getPosition();

        this->facing = sf::Vector2f(this->position.x, this->position.y - facing_offset);
        this->behind = sf::Vector2f(this->position.x, this->position.y + behind_offset);
        this->behind_far = sf::Vector2f(this->behind.x, this->behind.y + behind_far_offset);

        this->angle = -90;
    }

    Entity::Entity(const char *path, sf::IntRect rect)
    {
        this->texture = new sf::Texture();
        if (!this->texture->loadFromFile(path))
        {
            printf("Sprite creation failed %d %s", __LINE__, __FILE__);
            return;
        }
        this->sprite = new sf::Sprite(*this->texture);
        this->sprite->setTextureRect(rect);
        this->sprite->setOrigin(this->sprite->getGlobalBounds().width / 2, this->sprite->getGlobalBounds().height / 2);
        this->position = this->sprite->getPosition();

        this->facing = sf::Vector2f(this->position.x, this->position.y - facing_offset);
        this->behind = sf::Vector2f(this->position.x, this->position.y + behind_offset);
        this->behind_far = sf::Vector2f(this->behind.x, this->behind.y + behind_far_offset);

        this->angle = -90;
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

        this->facing = sf::Vector2f(this->position.x, this->position.y - facing_offset);
        this->behind = sf::Vector2f(this->position.x, this->position.y + behind_offset);
        this->behind_far = sf::Vector2f(this->behind.x, this->behind.y + behind_far_offset);

        this->sprite = sprite;
        this->angle = -90;
    }

    void Entity::FreeEntity()
    {
        free(this->sprite);
        free(this->texture);
        free(this);
    }

    void Entity::RotateSprite(float x, float y, int offset)
    {
        if (x == 0.0f && y == 0.0f)
            return;

        float angle_direction = atan2((this->position.y - y) - (this->position.y), (this->position.x - x) - (this->position.x));
        float save_angle = angle_direction * 180 / M_PI;
        
        angle_direction = angle_direction * 180 / M_PI - offset;
        this->facing = RotatePointAroundCenter(this->facing, this->position, angle_direction * M_PI / 180);
        this->behind = RotatePointAroundCenter(this->behind, this->position, angle_direction * M_PI / 180);
        this->behind_far = RotatePointAroundCenter(this->behind_far, this->position, angle_direction * M_PI / 180);
        this->angle = save_angle + 180;

        if (this->shift == 1 && this->right == 0 && this->left == 0 && this->up == 0 && this->down == 0)
            return;
        this->sprite->setRotation(angle_direction);
    }

    void Entity::Move(float x, float y)
    {

        this->sprite->move(sf::Vector2f(x, y));
        this->position = this->GetPos();

        if (x == 0.0f && y == 0.0f)
            return;
        this->facing = sf::Vector2f(this->position.x, this->position.y - facing_offset);
        this->behind = sf::Vector2f(this->position.x, this->position.y + behind_offset);
        this->behind_far = sf::Vector2f(this->behind.x, this->behind.y + behind_far_offset);
    }

    void Entity::SetPosition(sf::Vector2f pos)
    {
        this->sprite->setPosition(pos);
        this->position = this->GetPos();

        this->facing = sf::Vector2f(this->position.x, this->position.y - facing_offset);
        this->behind = sf::Vector2f(this->position.x, this->position.y + behind_offset);
        this->behind_far = sf::Vector2f(this->behind.x, this->behind.y + behind_far_offset);
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