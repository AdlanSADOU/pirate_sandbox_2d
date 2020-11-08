#include "game.h"

// extern S2D_Window *gWindow;
Entity playerClass;
// Enemy enemy;

sf::Sprite background;
float xAxis;
float yAxis;

void gameInput(sf::Event e)
{

    switch (e.type)
    {
    case sf::Event::EventType::KeyPressed:
        // if (e.key.code == sf::Keyboard::G)
        //     enemy.MovePosition(1, 1);
        // if (e.key.code == sf::Keyboard::Space)
        //     playerShoot();
        break;

    default:
        break;
    }
}

void gameInit()
{
    // background = S2D_CreateSprite("assets/background.jpg");
    // background->width = 3840;
    // background->height = 2160;

    // enemy = Enemy();
    playerClass = Entity("assets/PlayerRed_Frame_01_png_processed.png");
    // playerClass.SetSprite("assets/PlayerRed_Frame_01_png_processed.png");
    playerClass.SetPosition({100,100});
}

Entity *getPlayer()
{
    return (&playerClass);
}

void gameUpdate(update_args *args)
{
    playerClass.Move(xAxis, yAxis);
    playerClass.RotateSprite(xAxis, yAxis);
    // pushPart();
}

void gameRender()
{
    // S2D_DrawSprite(background);
    // engineParticules();
    // playerClass.Draw(false);
    printf("lollllllllllllllll\n");
    gWindow->draw(playerClass.sprite);
    // renderShoot();
}
