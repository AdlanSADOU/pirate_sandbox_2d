// game.h

#pragma once

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <SFML/OpenGL.hpp>
#include <gl/GLU.h>

// #include "simple2d.h"
#include "entity.h"
#include "enemy.h"
#include "ammunition.h"

#include "imgui/imgui-SFML.h"
#include "imgui/imgui.h"
#include <vector>
#include <cstdlib>

#ifndef M_PI
#define M_PI    3.14159265358979323846264338327950288   /* PI */
#endif

// extern S2D_Window *gWindow;
extern sf::RenderWindow *gWindow;
extern float deltaTime;
extern Entity playerClass;

extern float xAxis;
extern float yAxis;
extern bool up, down, left, right, shift;

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
void posDebug(sf::Vector2f pos);