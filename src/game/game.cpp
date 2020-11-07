#include "entity.h"
#include "enemy.h"
#include "game.h"
#include "vector"

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
    
    default:
        break;
    }
}

void gameInit()
{
    background = S2D_CreateSprite("assets/PixelBackgroundSeamlessVertically.png");
    background->width = gWindow->width;
    background->height = gWindow->height;
    

    enemy = Enemy();
    playerClass = Entity();
    playerClass.SetSprite("assets/PlayerRed_Frame_01_png_processed.png");
    playerClass.SetPosition(500,500);
    playerClass.SetClipRectangle(0, 0, 500, 256);
}

int x = 0;
void gameUpdate(update_args *args)
{
    playerClass.Move(xAxis, yAxis);
    playerClass.RotateSprite(xAxis, yAxis);
    if (S2D_Intersect_FRect(playerClass.GetRect(), enemy.entity.GetRect())) printf("%d collided!\n", ++x);
}

void gameRender()
{
    S2D_DrawSprite(background);
    playerClass.Draw(true);
    enemy.DrawEnemy();
}