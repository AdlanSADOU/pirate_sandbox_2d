#include "particules.h"

std::vector<Particule *> Particules;

float vector_normalize(sf::Vector2f vector)
{
    float normalize = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
    return (normalize);
}

Particule *createParticules(int offsetX, int offsetY, int size)
{
    Particule *part = new Particule();

    Entity *playerClass = getPlayer();
    sf::Vector2f playerBack = playerClass->behind;
    playerBack.x += offsetX;
    playerBack.y += offsetY;
    sf::Uint8 r = 255;
    sf::Uint8 g = 240;
    sf::Uint8 b = 0;
    sf::Uint8 a = 240;

    part->direction = RotatePointAroundCenter(playerClass->behind_far, playerClass->position, (-0.6f + float(rand() % 120 / 100.0f)));
     float angle_direction = atan2((part->direction.y - playerClass->position.y),
        (part->direction.x - playerClass->position.x));
    part->direction = sf::Vector2f(cos(angle_direction), sin(angle_direction));
    float normalize = vector_normalize(part->direction);
    part->direction = sf::Vector2f(part->direction.x / normalize, part->direction.y / normalize);

    part->triangle[0].position = sf::Vector2f(playerBack.x - size, playerBack.y - size);
    part->triangle[1].position = sf::Vector2f(playerBack.x + size, playerBack.y - size);
    part->triangle[2].position = sf::Vector2f(playerBack.x, playerBack.y + size);

    part->triangle[0].color = sf::Color{r, g, b, a};
    part->triangle[1].color = sf::Color{r, g, b, a};
    part->triangle[2].color = sf::Color{r, g, b, a};

    return (part);
}

void pushPart()
{
    int size = 2;
    for (int i = 0, value = 10; i != 6; i++) {
        Particules.push_back(createParticules(rand() % (value - value / 3), rand() % (value - value / 3), size));
        Particules.push_back(createParticules(-(rand() % (value - value / 3)), -(rand() % (value - value / 3)), size));
        Particules.push_back(createParticules(rand() % (value - value / 3), -(rand() % (value - value / 3)), size));
        Particules.push_back(createParticules(-(rand() % (value - value / 3)), rand() % (value - value / 3), size));
        Particules.push_back(createParticules(-(rand() % value), 0, size));
        Particules.push_back(createParticules(rand() % value, 0, size));
        Particules.push_back(createParticules(0, rand() % value, size));
        Particules.push_back(createParticules(0, -(rand() % value), size));
    }
}

void renderParticules()
{
    int speed = 3;

    for (int i = 0; i < Particules.size(); i++) {
        gWindow->draw(Particules[i]->triangle);

        Particules[i]->triangle[0].color.a -= 15;
        Particules[i]->triangle[1].color.a -= 15;
        Particules[i]->triangle[2].color.a -= 15;
        Particules[i]->triangle[0].color.g -= 15;
        Particules[i]->triangle[1].color.g -= 15;
        Particules[i]->triangle[2].color.g -= 15;

        Particules[i]->triangle[0].position.x += Particules[i]->direction.x * speed;
        Particules[i]->triangle[0].position.y += Particules[i]->direction.y * speed;
        Particules[i]->triangle[1].position.x += Particules[i]->direction.x * speed;
        Particules[i]->triangle[1].position.y += Particules[i]->direction.y * speed;
        Particules[i]->triangle[2].position.x += Particules[i]->direction.x * speed;
        Particules[i]->triangle[2].position.y += Particules[i]->direction.y * speed;

        if (Particules[i]->triangle[0].color.a <= 0) {
            delete(Particules[i]);
            Particules.erase(Particules.begin() + i);
        }
    }
}
