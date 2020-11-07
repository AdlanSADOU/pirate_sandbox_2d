#include "entity.h"
#include "enemy.h"
#include "game.h"
#include "ammunition.h"
#include <vector>

// extern S2D_Window *gWindow;
Entity playerClass;
Enemy enemy;

S2D_Sprite *background = NULL;
float xAxis;
float yAxis;

void gameInput(S2D_Event e)
{
    SDL_Keycode key = SDL_GetKeyFromName(e.key);
    
    switch (e.type)
    {
    case S2D_KEY_HELD:
        if (key == SDLK_g)
            enemy.MovePosition(1, 1);
        break;
        if (key == SDLK_x)
            playerShoot();

    
    default:
        break;
    }
}

void gameInit()
{
    background = S2D_CreateSprite("assets/background.jpg");
    background->width = 3840;
    background->height = 2160;
    
    playerClass = Entity();
    playerClass.SetSprite("assets/PlayerRed_Frame_01_png_processed.png");

    playerClass.SetPosition(S2D_Vec2f{1920/2, 1080/2});
}

Entity *getPlayer()
{
    return (&playerClass);
}

void gameUpdate(update_args *args)
{
    playerClass.Move(xAxis, yAxis);
    playerClass.RotateSprite(xAxis, yAxis);
}

void gameRender()
{
    S2D_DrawSprite(background);
    playerClass.Draw(false);
    renderShoot();
}
