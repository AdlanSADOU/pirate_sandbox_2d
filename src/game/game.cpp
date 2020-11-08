#include "game.h"

// extern S2D_Window *gWindow;
Entity playerClass;
Enemy enemy;

sf::Sprite background;
float xAxis;
float yAxis;

void gameInput(sf::Event e)
{

    switch (e.type)
    {
    case sf::Event::EventType::KeyPressed:
        if (e.key.code == sf::Keyboard::G)
            enemy.MovePosition(1, 1);
        if (e.key.code == sf::Keyboard::Space)
            playerShoot();
        break;

    default:
        break;
    }
}

void gameInit()
{
    enemy = Enemy();
    playerClass = Entity("assets/PlayerRed_Frame_01_png_processed.png");
    playerClass.SetPosition({100,100});
}

void gameUpdate(update_args *args)
{
    playerClass.Move(xAxis, yAxis);
    playerClass.RotateSprite(xAxis, yAxis);
    pushPart();
}

void gameRender()
{
    engineParticules();
    gWindow->draw(*playerClass.sprite);
    gWindow->draw(*enemy.entity.sprite);
    renderShoot();
}

Entity *getPlayer()
{
    return (&playerClass);
}