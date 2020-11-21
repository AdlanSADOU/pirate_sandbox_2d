// Particules.h

#pragma once

#include <SFML/System.hpp>
#include "entity.h"

class Particule
{
public:
    sf::Color startColor;
    sf::Color endColor;
    sf::VertexArray circle;
    sf::Vector2f direction;
    sf::Vector2f randomDirection;
    int life;
    float timeStep;
    bool dead = false;

    Particule()
    {
        this->circle = sf::VertexArray(sf::Points, 1);
    }
};

class ParticleSystem
{
    std::vector<Particule *> Particules;
    Particule *createParticules(int offsetX, int offsetY, sf::Vector2f randomDirection, Entity &entity, sf::Color startColor, sf::Color endColor, int life);
public:

    ParticleSystem(){};

    void Update(Entity &entity, int offsetX, int offsetY, float x, float y, sf::Color startColor, sf::Color endColor, int life);
    sf::Color RgbInterpolation(sf::Color startColor, float timeStep, sf::Color endColor);
    void Render(sf::RenderWindow &window);
};