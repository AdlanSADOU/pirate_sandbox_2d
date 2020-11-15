// game.h
// The main game scene

#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GLU.h>

#include <vector>
#include <cstdlib>

#include "imgui-common.h"

/*
 * These will no longer be globally included 
 * they'll be explicitly included in those files that directly need them.
 * rest in peace, compiler.
 */
// #include "utils.h"
// #include "entity.h"
// #include "particles.h"
// #include "enemy.h"
// #include "ammunition.h"

#ifndef M_PI
#define M_PI    3.14159265358979323846264338327950288   /* PI */
#endif

typedef struct args
{
    char *str;
    int i;
} update_args;

// Game
void gameInit();
void gameUpdate(float dt);
void gameRender(sf::RenderWindow &window);
void gameInput(sf::Event e);
void posDebug(sf::Vector2f pos);