#include "particles.h"

std::vector<Particule *> Particules;

float vector_magnitude(sf::Vector2f vector)
{
    float magnitude = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
    return (magnitude);
}

Particule *createParticules(int offsetX, int offsetY, int size, sf::Vector2f randomDirection)
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

    part->randomDirection = randomDirection;

    part->circle[0].position = playerBack;
    part->circle[0].color = sf::Color{r, g, b, a};

    return (part);
}

void pushPart()
{
    Entity *playerClass = getPlayer();
    int size = 5, number = vector_magnitude(sf::Vector2f(xAxis, yAxis));
    if (number == 0) number = 1;
    else if (number > 3) number = 3;
    sf::Vector2f randomDirection = GetRandomNormalizedVector();

    for (int i = 0, value = 10; i != number; i++) {
        Particules.push_back(createParticules(rand() % (value - value / 3), rand() % (value - value / 3), size, randomDirection));
        randomDirection = GetRandomNormalizedVector();
        Particules.push_back(createParticules(-(rand() % (value - value / 3)), -(rand() % (value - value / 3)), size, randomDirection));
        randomDirection = GetRandomNormalizedVector();
        Particules.push_back(createParticules(rand() % (value - value / 3), -(rand() % (value - value / 3)), size, randomDirection));
        randomDirection = GetRandomNormalizedVector();
        Particules.push_back(createParticules(-(rand() % (value - value / 3)), rand() % (value - value / 3), size, randomDirection));
        randomDirection = GetRandomNormalizedVector();
    }
}

void renderParticules()
{

    int speed = vector_magnitude(sf::Vector2f(xAxis, yAxis)) / 2;
    if (speed == 0) speed = 1;
    else if (speed > 5) speed = 5;

    /*sf::RenderStates state;
    state.shader = nullptr;
    state.texture = nullptr;
    state.blendMode = sf::BlendAlpha;*/

    for (int i = 0; i < Particules.size(); i++) {
        gWindow->draw(Particules[i]->circle);

        Particules[i]->circle[0].color.a -= 15;
        Particules[i]->circle[0].color.g -= 15;
        
        Particules[i]->circle[0].position.x += Particules[i]->direction.x * (Particules[i]->randomDirection.x * speed);
        Particules[i]->circle[0].position.y += Particules[i]->direction.y * (Particules[i]->randomDirection.y * speed);

        if (Particules[i]->circle[0].color.g <= 0) {
            delete(Particules[i]);
            Particules.erase(Particules.begin() + i);
        }
    }
    ImGui::Text("Particle count: %d", Particules.size());
}