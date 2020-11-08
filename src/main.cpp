#include "game.h"

S2D_Window *gWindow = NULL;
S2D_Text *fps;

float speed = 0.1f;

void onKeyHeld(SDL_Keycode key)
{
    switch (key) {
    case SDLK_w:
        (yAxis) -= gWindow->deltaTime * speed;
        break;
    case SDLK_a:
        (xAxis) -= gWindow->deltaTime * speed;
        break;
    case SDLK_s:
        (yAxis) += gWindow->deltaTime * speed;
        break;
    case SDLK_d:
        (xAxis) += gWindow->deltaTime * speed;
        break;
    case SDLK_SPACE:
        if (yAxis > -0.16f && yAxis < 0.01f) yAxis = 0;
        ((yAxis) -= yAxis / 20);
        if (xAxis > -0.16f && xAxis < 0.01f) xAxis = 0;
        ((xAxis) -= xAxis / 20);
        break;
    default:
        break;
    }
}

void onKeyUp(SDL_Keycode key)
{

}

void onKeyDown(SDL_Keycode key)
{

}

void onKeyCallback(S2D_Event e)
{
    SDL_Keycode key = SDL_GetKeyFromName(e.key);

    gameInput(e);

    switch (e.type)
    {
    case S2D_KEY_UP:
        key == SDLK_ESCAPE ? S2D_Close(gWindow) : 0;
        onKeyUp(key);
        break;

    case S2D_KEY_HELD:
        onKeyHeld(key);
        break;

    case S2D_KEY_DOWN:
        onKeyDown(key);
        break;
    default:
        break;
    }
}

void update(void *args)
{
    update_args *a_args = (update_args *)(args);

    S2D_SetText(fps, "FPS:  %.2f  -  deltaTime:  %.2f", gWindow->fps, gWindow->deltaTime);

    gameUpdate(a_args);
}

void render()
{
    gameRender();
    S2D_DrawText(fps);
}

int main(int argc, char *argv[])
{
    update_args u_args;
    gWindow = S2D_CreateWindow("Awesome Sample", 1920, 1080, update, render, S2D_RESIZABLE | S2D_HIGHDPI);
    gWindow->background = {.12f, .10f, .10f, 0.1f};
    gWindow->on_UpdateArgs = (&u_args);
    gWindow->viewport.mode = S2D_EXPAND;
    gWindow->on_key = onKeyCallback;
    gWindow->fps_cap = 60;
    gWindow->vsync = true;
    gWindow->deltaTime = 1;

    fps = S2D_CreateText("assets/fonts/space_invaders.ttf", "Hello Space!", 20);
    gameInit();

    S2D_Show(gWindow);
    return 0;
}
