#include "game.h"

// extern S2D_Window *gWindow;
Entity playerClass;
ParticlePool particlePool;

sf::Sprite background;
float xAxis;
float yAxis;

bool space = false;

float vector_magnitude(sf::Vector2f vector)
{
    float magnitude = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
    return (magnitude);
}

void gameInput(sf::Event e)
{
    switch (e.type)
    {
    case sf::Event::EventType::KeyPressed:
        if (e.key.code == sf::Keyboard::Space)
            space = true;
        if (e.key.code == sf::Keyboard::B)
            PushEnemy();
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
    particlePool = ParticlePool();
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

void PushEngineParticules()
{
    int size = 2;
    int loop = vector_magnitude(sf::Vector2f(xAxis, yAxis));
    if (loop == 0)
        loop = 1;
    int speed = loop / 2;
    if (speed == 0)
        speed = 1;
    int life = 20;

    sf::Vector2f playerBack = playerClass.behind;

    sf::Vector2f direction = RotatePointAroundCenter(playerClass.behind_far, playerClass.position, (-0.6f + float(rand() % 120 / 100.0f)));
    float angle_direction = atan2((direction.y - playerClass.position.y), (direction.x - playerClass.position.x));
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
}

void renderEngineParticules()
{
    particlePool.Update(gWindow);
}

void gameUpdate()
{
    playerClass.Move(xAxis, yAxis);
    playerClass.RotateSprite(xAxis, yAxis, 90);
    if (space) {
        playerShoot();
    }
    PushEngineParticules();
    cameraMove();
}

void posDebug(sf::Vector2f pos)
{
    sf::CircleShape dot = sf::CircleShape();
    dot.setPosition({pos.x - 2, pos.y - 2});
    dot.setFillColor(sf::Color::White);
    dot.setRadius(4.0f);
    gWindow->draw(dot);
}

void gameRender()
{
    renderEngineParticules();
    RenderShoot();
    RenderEnnemies();
    gWindow->draw(*playerClass.sprite);

    ImGui::Text("Particules count: %d", particlePool.CountParticleAlive());
    /*posDebug(playerClass.facing);
    posDebug(playerClass.position);
    posDebug(playerClass.behind);*/
}

Entity *getPlayer()
{
    return (&playerClass);
}

sf::Vector2f RotatePointAroundCenter(sf::Vector2f point, sf::Vector2f center, float angle_rad)
{
    float sin_val = sin(angle_rad);
    float cos_val = cos(angle_rad);

    // translate point back to origin:
    point.x -= center.x;
    point.y -= center.y;

    // rotate point
    float xnew = point.x * cos_val - point.y * sin_val;
    float ynew = point.x * sin_val + point.y * cos_val;

    // translate point back:
    point.x = xnew + center.x;
    point.y = ynew + center.y;

    return (point);
}