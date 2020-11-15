// Particules.h

#pragma once

#include <SFML/System.hpp>
#include "entity.h"


class Particule
{
public:
    sf::Color color;
    sf::VertexArray circle;
    sf::Vector2f direction;
    sf::Vector2f randomDirection;
    bool dead = false;

    Particule()
    {
        this->circle = sf::VertexArray(sf::Points, 1);
    }
};

class ParticleSystem
{
    
    std::vector<Particule *> Particules;
    Particule *createParticules(int offsetX, int offsetY, int size, sf::Vector2f randomDirection, Entity &entity);
public:
    ParticleSystem(){};
    void Update(Entity &entity);
    void Render(sf::RenderWindow &window);
};