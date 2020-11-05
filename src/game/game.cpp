#include "game.h"
#include "enemy.h"
#include "vector"

Entity *player = NULL;
Entity playerClass;
Enemy *enemy = new Enemy();

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
            enemy->MovePosition(1, 1);
        break;
    
    default:
        break;
    }
}

void gameInit()
{
    background = S2D_CreateSprite("assets/PixelBackgroundSeamlessVertically.png");
    background->width = 800;
    background->height = 600;


    player = new Entity("assets/PlayerRed_Frame_01_png_processed.png");
    playerClass = Entity();
    playerClass.SetSprite("assets/PlayerRed_Frame_01_png_processed.png");
    playerClass.SetPosition(500,500);
}

void gameUpdate(update_args *args)
{
    // sdEntityMove(player, xAxis, yAxis);
    playerClass.Move(xAxis, yAxis);
    playerClass.RotateSprite(xAxis, yAxis);
}

void gameRender()
{
    S2D_DrawSprite(background);
    // sdEntityDraw(player, false);
    playerClass.Draw(false);
    enemy->DrawEnemy();
}