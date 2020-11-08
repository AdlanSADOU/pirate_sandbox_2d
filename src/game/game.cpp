#include "game.h"

// extern S2D_Window *gWindow;
Entity playerClass;
Enemy enemy;

sf::Sprite background;
float xAxis;
float yAxis;

bool space = false;

void gameInput(sf::Event e)
{

    switch (e.type)
    {
    case sf::Event::EventType::KeyPressed:
        if (e.key.code == sf::Keyboard::Space)
            space = true;
        break;
    case sf::Event::EventType::KeyReleased:
        if (e.key.code == sf::Keyboard::Space)
            space = false;
        break;

    default:
        break;
    }
}

void gameInit()
{
    playerClass = Entity("assets/PlayerRed_Frame_01_png_processed.png");
    playerClass.SetPosition({100,100});
}

void gameUpdate(update_args *args)
{
    playerClass.Move(xAxis, yAxis);
    playerClass.RotateSprite(xAxis, yAxis);
    if (space) {
        playerShoot();
    }
    pushPart();
}

void gameRender()
{
    engineParticules();
    gWindow->draw(*playerClass.sprite);
    renderShoot();
}

Entity *getPlayer()
{
    return (&playerClass);
}