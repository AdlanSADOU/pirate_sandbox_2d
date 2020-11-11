// Particules.h

#pragma once

#include "game.h"

class Particule {
public:
    sf::Color color;
    sf::VertexArray triangle;
    sf::Vector2f direction;
    bool dead = false;
    
    Particule() {
        this->triangle = sf::VertexArray(sf::Triangles, 3);
    }
};

void renderParticules();
void pushPart(void);
float vector_magnitude(sf::Vector2f vector);