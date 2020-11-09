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
    playerClass.SetPosition({3840 / 2, 2160 / 2});
}

void cameraMove()
{
    sf::View view = sf::View();
    view.setSize({(float)gWindow->getSize().x, (float)gWindow->getSize().y});
    sf::Vector2f playerPos = playerClass.GetPos();
    if (playerPos.x >= 3200)
        playerPos.x = 3200;
    if (playerPos.y >= 1800)
        playerPos.y = 1800;
    if (playerPos.x <= 640)
        playerPos.x = 640;
    if (playerPos.y <= 360)
        playerPos.y = 360;
    view.setCenter(playerPos);
    gWindow->setView(view);
}

void gameUpdate()
{
    playerClass.Move(xAxis, yAxis);
    playerClass.RotateSprite(xAxis, yAxis);
    if (space) {
        playerShoot();
    }
    pushPart();
    cameraMove();
}

void gameRender()
{
    engineParticules();
    gWindow->draw(*playerClass.sprite);
    RenderShoot();
    sf::CircleShape fion = sf::CircleShape();
    fion.setPosition({playerClass.facing.x - 2, playerClass.facing.y - 2});
    fion.setFillColor(sf::Color::White);
    fion.setRadius(4.0f);
    sf::CircleShape fiak = sf::CircleShape();
    fiak.setPosition({playerClass.position.x - 2, playerClass.position.y - 2});
    fiak.setFillColor(sf::Color::White);
    fiak.setRadius(4.0f);
    gWindow->draw(fion);
    gWindow->draw(fiak);
}

Entity *getPlayer()
{
    return (&playerClass);
}