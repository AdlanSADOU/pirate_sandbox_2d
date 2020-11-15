#include "particles.h"

#include "utils.h"
#include "imgui-common.h"

extern float xAxis, yAxis;

Particule *ParticleSystem::createParticules(int offsetX, int offsetY, int size, sf::Vector2f randomDirection, Entity &entity)
{
    Particule *part = new Particule();

    sf::Vector2f playerBack = entity.behind;
    playerBack.x += offsetX;
    playerBack.y += offsetY;
    sf::Uint8 r = 255, g = 240, b = 0, a = 240;

    part->direction = utils::RotatePointAroundCenter(entity.behind_far, entity.position, (-0.6f + float(rand() % 120 / 100.0f)));
    float angle_direction = atan2((part->direction.y - entity.position.y),
                                  (part->direction.x - entity.position.x));
    part->direction = sf::Vector2f(cos(angle_direction), sin(angle_direction));
    float magnitude = utils::VectorMagnitude(part->direction);
    part->direction = sf::Vector2f(part->direction.x / magnitude, part->direction.y / magnitude);

    part->randomDirection = randomDirection;

    part->circle[0].position = playerBack;
    part->circle[0].color = sf::Color{r, g, b, a};

    return (part);
}

void ParticleSystem::Update(Entity &entity)
{
    int size = 5, number = utils::VectorMagnitude(sf::Vector2f(xAxis, yAxis));
    if (number == 0)
        number = 1;
    else if (number > 3)
        number = 3;
    int speed = utils::VectorMagnitude(sf::Vector2f(xAxis, yAxis)) / 2;
    if (speed == 0)
        speed = 1;
    else if (speed > 5)
        speed = 5;

    sf::Vector2f randomDirection = utils::GetRandomNormalizedVector();

    for (int i = 0, value = 10; i != number; i++)
    {
        Particules.push_back(createParticules(rand() % (value - value / 3), rand() % (value - value / 3), size, randomDirection, entity));
        randomDirection = utils::GetRandomNormalizedVector();
        Particules.push_back(createParticules(-(rand() % (value - value / 3)), -(rand() % (value - value / 3)), size, randomDirection, entity));
        randomDirection = utils::GetRandomNormalizedVector();
        Particules.push_back(createParticules(rand() % (value - value / 3), -(rand() % (value - value / 3)), size, randomDirection, entity));
        randomDirection = utils::GetRandomNormalizedVector();
        Particules.push_back(createParticules(-(rand() % (value - value / 3)), rand() % (value - value / 3), size, randomDirection, entity));
        randomDirection = utils::GetRandomNormalizedVector();
    }

    for (int i = 0; i < Particules.size(); i++)
    {
        Particules[i]->circle[0].color.a -= 15;
        Particules[i]->circle[0].color.g -= 15;

        Particules[i]->circle[0].position.x += Particules[i]->direction.x * (Particules[i]->randomDirection.x * speed);
        Particules[i]->circle[0].position.y += Particules[i]->direction.y * (Particules[i]->randomDirection.y * speed);

        if (Particules[i]->circle[0].color.g <= 0)
        {
            delete (Particules[i]);
            Particules.erase(Particules.begin() + i);
        }
    }
}

void ParticleSystem::Render(sf::RenderWindow &window)
{
    /*sf::RenderStates state;
    state.shader = nullptr;
    state.texture = nullptr;
    state.blendMode = sf::BlendAlpha;*/

    for (int i = 0; i < Particules.size(); i++)
    {
        window.draw(Particules[i]->circle);
    }

    ImGui::Text("Particle count: %d", Particules.size());
}