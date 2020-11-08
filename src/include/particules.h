// Particules.h

#pragma once

#include "game.h"

typedef struct {
    sf::FloatRect rect;
    sf::Color color;
} Particule;

void engineParticules(void);
void renderParticules(std::vector<Particule *> Particules);
void pushPart(void);