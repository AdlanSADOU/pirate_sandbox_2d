/*#include "particules.h"

std::vector<Particule *> Particules;

float vector_magnitude(sf::Vector2f vector)
{
    float magnitude = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
    return (magnitude);
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
    float magnitude = vector_magnitude(part->direction);
    part->direction = sf::Vector2f(part->direction.x / magnitude, part->direction.y / magnitude);

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
    int size = 2, number = vector_magnitude(sf::Vector2f(xAxis, yAxis));
    if (number == 0) number = 1;

    for (int i = 0, value = 10; i != number * 2; i++) {
        Particules.push_back(createParticules(rand() % (value - value / 3), rand() % (value - value / 3), size));
        Particules.push_back(createParticules(-(rand() % (value - value / 3)), -(rand() % (value - value / 3)), size));
        Particules.push_back(createParticules(rand() % (value - value / 3), -(rand() % (value - value / 3)), size));
        Particules.push_back(createParticules(-(rand() % (value - value / 3)), rand() % (value - value / 3), size));
    }
}

void renderParticules()
{

    int speed = vector_magnitude(sf::Vector2f(xAxis, yAxis)) / 2;
    if (speed == 0) speed = 1;

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
*/