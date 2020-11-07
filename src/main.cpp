#include "game.h"

// SDL_main.h is included automatically from SDL.h

// #ifdef main
// #undef main
// #endif

// #ifdef SDL_Main
// #undef SDL_Main
// #endif

// #ifndef SDL_Main
// #define SDL_Main
// #endif

S2D_Window *gWindow;
float speed = .01f;
float gDeltaTime = 0.f;
S2D_Text *fps;

void move_sprite(SDL_Keycode key)
{
    switch (key) {
    case SDLK_w: (yAxis) -= gDeltaTime * speed;
        break;
    case SDLK_a: (xAxis) -= gDeltaTime * speed;
        break;
    case SDLK_s: (yAxis) += gDeltaTime * speed;
        break;
    case SDLK_d: (xAxis) += gDeltaTime * speed;
        break;
    case SDLK_SPACE:
        if (yAxis > -0.16 && yAxis < 0.01) yAxis = 0;
        else (yAxis > 0) ? ((yAxis) -= gDeltaTime * speed) : ((yAxis) += gDeltaTime * speed);
        if (xAxis > -0.16 && xAxis < 0.01) xAxis = 0;
        else (xAxis > 0) ? ((xAxis) -= gDeltaTime * speed) : ((xAxis) += gDeltaTime * speed);
        break;
    case SDLK_x: printf(".\n"); //TODO implémenter les fonction pour tirer.
    default:
        break;
    }
}

void sdOnKeyCallback(S2D_Event e)
{
    SDL_Keycode key = SDL_GetKeyFromName(e.key);
    gameInput(e);
    switch (e.type) {
        case S2D_KEY_UP: key == SDLK_ESCAPE ? S2D_Close(gWindow) : 0;
            break;

        case S2D_KEY_HELD: move_sprite(key);
            break;
        default:
        break;
    }
}

void update(void* args)
{
    update_args *a_args = (update_args *)(args);

    gDeltaTime = (float)(1/gWindow->fps)*1000;
    S2D_SetText(fps, "FPS:  %.2f  -  deltaTime:  %.2f", gWindow->fps, gDeltaTime);

    gameUpdate(a_args);
}

void render()
{
    gameRender();
    S2D_DrawText(fps);
}

int main(int argc, char * argv[])
{
    update_args u_args;
    gWindow = S2D_CreateWindow("Awesome Sample", 800, 600, update, render, S2D_RESIZABLE);
    gWindow->background      = { .12f, .10f, .10f};
    gWindow->on_UpdateArgs  = (&u_args);
    gWindow->viewport.mode   = S2D_SCALE;
    gWindow->on_key          = sdOnKeyCallback;
    gWindow->fps_cap         = 60;
    
    fps = S2D_CreateText("assets/fonts/space_invaders.ttf", "Hello Space!", 20);
    // S2D_SetText()
    gameInit();

    S2D_Show(gWindow);
    return 0;
}
