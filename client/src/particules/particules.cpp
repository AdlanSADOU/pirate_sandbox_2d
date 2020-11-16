#include "particles.h"

#include "utils.h"
#include "imgui-common.h"

extern float xAxis, yAxis;

sf::Color ParticleSystem::RgbInterpolation(sf::Color startColor, float timeStep, sf::Color endColor)
{
	sf::Color finalColor;

	finalColor.r = startColor.r + (endColor.r - startColor.r) * timeStep;
	finalColor.g = startColor.g + (endColor.g - startColor.g) * timeStep;
	finalColor.b = startColor.b + (endColor.b - startColor.b) * timeStep;
	finalColor.a = startColor.a + (endColor.a - startColor.a) * timeStep;

	return (finalColor);
}

Particule *ParticleSystem::createParticules(int offsetX, int offsetY, sf::Vector2f randomDirection, Entity &entity, sf::Color startColor, sf::Color endColor, int life)
{
    Particule *part = new Particule();

    sf::Vector2f playerBack = entity.behind;
    playerBack.x += offsetX;
    playerBack.y += offsetY;

    part->direction = utils::RotatePointAroundCenter(entity.behind_far, entity.position, (-0.6f + float(rand() % 120 / 100.0f)));
    float angle_direction = atan2((part->direction.y - entity.position.y),
                                  (part->direction.x - entity.position.x));
    part->direction = sf::Vector2f(cos(angle_direction), sin(angle_direction));
    float magnitude = utils::VectorMagnitude(part->direction);
    part->direction = sf::Vector2f(part->direction.x / magnitude, part->direction.y / magnitude);

    part->randomDirection = randomDirection;
    part->timeStep = 0.0f;
    part->life = life;
    part->startColor = startColor;
    part->endColor = endColor;
    part->circle[0].position = playerBack;
    part->circle[0].color = RgbInterpolation(part->startColor, part->timeStep, part->endColor);

    return (part);
}

void ParticleSystem::Update(Entity &entity, int offsetX, int offsetY, float x, float y, sf::Color startColor, sf::Color endColor, int life)
{
    int number = utils::VectorMagnitude(sf::Vector2f(x, y));
    if (number == 0)
        number = 1;
    else if (number > 3)
        number = 3;

    int speed = utils::VectorMagnitude(sf::Vector2f(x, y)) / 2;
    if (speed == 0)
        speed = 1;
    else if (speed > 5)
        speed = 5;

    sf::Vector2f randomDirection = utils::GetRandomNormalizedVector();

    for (int i = 0, value = 10; i != number; i++)
    {
        Particules.push_back(createParticules(rand() % (value - value / 3) + offsetX, rand() % (value - value / 3) + offsetY, randomDirection, entity, startColor, endColor, life));
        randomDirection = utils::GetRandomNormalizedVector();
        Particules.push_back(createParticules(-(rand() % (value - value / 3) + offsetX), -(rand() % (value - value / 3) + offsetY), randomDirection, entity, startColor, endColor, life));
        randomDirection = utils::GetRandomNormalizedVector();
        Particules.push_back(createParticules(rand() % (value - value / 3) + offsetX, -(rand() % (value - value / 3) + offsetY), randomDirection, entity, startColor, endColor, life));
        randomDirection = utils::GetRandomNormalizedVector();
        Particules.push_back(createParticules(-(rand() % (value - value / 3) + offsetX), rand() % (value - value / 3) + offsetY, randomDirection, entity, startColor, endColor, life));
        randomDirection = utils::GetRandomNormalizedVector();
    }

    for (int i = 0; i < Particules.size(); i++)
    {
        Particules[i]->timeStep += 1.0f / Particules[i]->life;
        sf::Color resColor = RgbInterpolation(Particules[i]->startColor, Particules[i]->timeStep, Particules[i]->endColor);

        Particules[i]->circle[0].color = resColor;
        Particules[i]->circle[0].position.x += Particules[i]->direction.x * (Particules[i]->randomDirection.x * speed);
        Particules[i]->circle[0].position.y += Particules[i]->direction.y * (Particules[i]->randomDirection.y * speed);

        if (Particules[i]->timeStep > 1.0f)
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