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

void engineParticules(void);
void renderParticules(std::vector<Particule *> Particules);
void pushPart(void);