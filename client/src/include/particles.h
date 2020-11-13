// Particules.h

#pragma once

#include "game.h"

class Particule {
public:
    sf::Color color;
    sf::VertexArray circle;
    sf::Vector2f direction;
    sf::Vector2f randomDirection;
    bool dead = false;
    
    Particule() {
        this->circle = sf::VertexArray(sf::Points, 1);
    }
};

void renderParticules();
void pushPart(void);
float vector_magnitude(sf::Vector2f vector);