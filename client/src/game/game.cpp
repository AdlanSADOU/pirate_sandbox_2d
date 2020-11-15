//#include "game.h"

#include "game.h"
#include "client.h"
#include "player.h"
#include "enemy.h"

sf::Sprite background;
extern float xAxis;
extern float yAxis;
extern bool space;

Player player;

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
    //particlePool = ParticlePool();
}

/*void PushEngineParticules()
{
    int size = 2;
    int loop = vector_magnitude(sf::Vector2f(xAxis, yAxis));
    if (loop == 0)
        loop = 1;
    int speed = loop / 2;
    if (speed == 0)
        speed = 1;
    int life = 20;

    sf::Vector2f playerBack = player.playerClass.behind;

    sf::Vector2f direction = RotatePointAroundCenter(player.playerClass.behind_far, player.playerClass.position, (-0.6f + float(rand() % 120 / 100.0f)));
    float angle_direction = atan2((direction.y - player.playerClass.position.y), (direction.x - player.playerClass.position.x));
    direction = sf::Vector2f(cos(angle_direction), sin(angle_direction));
    float magnitude = vector_magnitude(direction);
    direction = sf::Vector2f(direction.x / magnitude, direction.y / magnitude);
    sf::Vector2f randomDirection = GetRandomNormalizedVector();

    sf::Color startColor = {255, 255, 0, 255};
    sf::Color endColor = {255, 0, 0, 0};

    for (int i = 0, value = 6; i != loop * 2; i++) {
        particlePool.Generate(sf::Vector2f(playerBack.x + rand() % (value - value / 3), playerBack.y + rand() % (value - value / 3)), speed, direction, randomDirection, size, life, startColor, endColor, sf::BlendAdd);
        randomDirection = GetRandomNormalizedVector();
        particlePool.Generate(sf::Vector2f(playerBack.x + (-(rand() % (value - value / 3))), playerBack.y + (-(rand() % (value - value / 3)))), speed, direction, randomDirection, size, life, startColor, endColor, sf::BlendAdd);
        randomDirection = GetRandomNormalizedVector();
        particlePool.Generate(sf::Vector2f(playerBack.x + rand() % (value - value / 3), playerBack.y + (-(rand() % (value - value / 3)))), speed, direction, randomDirection, size, life, startColor, endColor, sf::BlendAdd);
        randomDirection = GetRandomNormalizedVector();
        particlePool.Generate(sf::Vector2f(playerBack.x + (-(rand() % (value - value / 3))), playerBack.y + rand() % (value - value / 3)), speed, direction, randomDirection, size, life, startColor, endColor, sf::BlendAdd);
        randomDirection = GetRandomNormalizedVector();
    }
}*/

/*void renderEngineParticules()
{
    particlePool.Update(gWindow);
}
*/

void gameUpdate(float dt)
{
    player.Update();
    //PushEngineParticules();

}

void gameRender(sf::RenderWindow &window)
{
    //renderEngineParticules();
    // RenderShoot();
    CameraFollow(player.entity, window);
    player.Render(window);
    RenderEnnemies(window);
    // window.draw(*player.entity.sprite);
    //ImGui::Text("Particle count: %d", particlePool.CountParticleAlive());
    /*posDebug(playerClass.facing);
    posDebug(playerClass.position);
    posDebug(playerClass.behind);*/
}

void posDebug(sf::Vector2f pos, sf::RenderWindow &window)
{
    sf::CircleShape dot = sf::CircleShape();
    dot.setPosition({pos.x - 2, pos.y - 2});
    dot.setFillColor(sf::Color::White);
    dot.setRadius(4.0f);
    window.draw(dot);
}

Entity *getPlayer()
{
    return (&player.entity);
}
