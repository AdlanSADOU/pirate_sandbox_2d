// Particules.h

#pragma once

#include "game.h"

typedef struct {
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
} P_Color;

typedef struct {
    S2D_FRect rect;
    P_Color color;
} Particule;

void engineParticules(void);
void renderParticules(std::vector<Particule *> Particules);
void pushPart(void);