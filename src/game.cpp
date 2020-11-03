#include "game.h"
#include "vector"

sdEntity *player = NULL;
S2D_Sprite *background = NULL;
float xAxis;
float yAxis;

void gameInit()
{
    background = S2D_CreateSprite("assets/PixelBackgroundSeamlessVertically.png");
    background->width = 800;
    background->height = 600;

    player = sdEntityCreate("assets/PlayerRed_Frame_01_png_processed.png");
}

void gameUpdate(update_args *args)
{
    sdEntityMove(player, xAxis, yAxis);
}

void gameRender()
{
    S2D_DrawSprite(background);
    sdEntityDraw(player, false);
}