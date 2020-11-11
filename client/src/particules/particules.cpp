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
    sf::Uint8 r = 255, g = 240, b = 0, a = 240;

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
    Entity *playerClass = getPlayer();

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

        for (int j = 0; j != 3; j++) {
            Particules[i]->triangle[j].color.a -= 15;
            Particules[i]->triangle[j].color.g -= 15;
        }
        for (int j = 0; j != 3; j++) {
            Particules[i]->triangle[j].position.x += Particules[i]->direction.x * speed;
            Particules[i]->triangle[j].position.y += Particules[i]->direction.y * speed;
        }
        if (Particules[i]->triangle[0].color.g <= 0) {
            delete(Particules[i]);
            Particules.erase(Particules.begin() + i);
        }
    }
    ImGui::Text("Particules count: %d", Particules.size());
}
