//#include "game.h"

#include "game.h"
#include "client.h"
#include "player.h"
#include "enemy.h"
#include <cmath>
#include <algorithm>

void CameraFollow(Entity entity, sf::RenderWindow &window);


// extern float xAxis;
// extern float yAxis;
// extern bool space;

sf::Sprite background;
Player player;

void gameInput(sf::Event e)
{
    switch (e.type)
    {
    case sf::Event::EventType::KeyPressed:
        
        if (e.key.code == sf::Keyboard::B)
            CreateEnemy();
        break;


    default:
        break;
    }
}

void gameInit()
{
    player = Player("assets/PlayerRed_Frame_01_png_processed.png");
}

void gameUpdate(float dt)
{
    player.Update();
}

void gameRender(sf::RenderWindow &window)
{
    CameraFollow(player.entity, window);
    player.Render(window);
    RenderEnnemies(window);
}

Entity *getPlayer()
{
    return (&player.entity);
}

void CameraFollow(Entity entity, sf::RenderWindow &window)
{
    sf::View view = sf::View();
    view.setSize({(float)window.getSize().x, (float)window.getSize().y});

    sf::Vector2f entityPos = entity.GetPos();

    if (entityPos.x >= 3200)
        entityPos.x = 3200;
    if (entityPos.y >= 1800)
        entityPos.y = 1800;
    if (entityPos.x <= 640)
        entityPos.x = 640;
    if (entityPos.y <= 360)
        entityPos.y = 360;

    view.setCenter(entityPos);
    window.setView(view);
}