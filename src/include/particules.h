// Particules.h

#pragma once

#include "game.h"

typedef struct {
    sf::Uint8 r;
    sf::Uint8 g;
    sf::Uint8 b;
    sf::Uint8 a;
} P_Color;

typedef struct {
    sf::FloatRect rect;
    P_Color color;
} Particule;

void engineParticules(void);
void renderParticules(std::vector<Particule *> Particules);
void pushPart(void);