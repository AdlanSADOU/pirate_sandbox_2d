// game.h

#pragma once

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

// #include "simple2d.h"
#include "entity.h"
#include "enemy.h"
#include "ammunition.h"
#include "particules.h"

#include <vector>

#ifndef M_PI
#define M_PI    3.14159265358979323846264338327950288   /**< pi */
#endif

// extern S2D_Window *gWindow;
extern sf::RenderWindow *gWindow;
extern float deltaTime;
extern Entity playerClass;

extern float xAxis;
extern float yAxis;

typedef struct args
{
    char *str;
    int i;
} update_args;

// Game
void gameInit();
void gameUpdate();
void gameRender();
Entity *getPlayer();
void gameInput(sf::Event e);
