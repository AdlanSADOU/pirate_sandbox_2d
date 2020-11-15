//#include "game.h"

#include "game.h"
#include "particles.h"
#include "client.h"

class Player
{
public:
    Entity entity;
    Projectiles projectile;
    ParticleSystem particleSystem;

    Player(){};
    Player(const char *path) {
        entity = Entity(path);
        entity.SetPosition({3840 / 2, 2160 / 2});
    }

    void Update() {
        particleSystem.pushPart(entity);
    }

    void Render() {
        projectile.RenderShoot();
        particleSystem.renderParticules();
    }

    void Move(float xAxis, float yAxis) {
        entity.up = up;
        entity.down = down;
        entity.right = right;
        entity.left = left;

        entity.Move(xAxis, yAxis);
        entity.RotateSprite(xAxis, yAxis, 90);
    }

    void Shoot(bool key) {
        if (key) {
            projectile.PlayerShoot(&this->entity);
        }
    }
};

//ParticlePool particlePool;
Player player;
sf::Sprite background;
float xAxis;
float yAxis;

bool space = false;

/*float vector_magnitude(sf::Vector2f vector)
{
    float magnitude = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
    return (magnitude);
}*/

void CameraFollow(Entity entity)
    {
        sf::View view = sf::View();
        view.setSize({(float)gWindow->getSize().x, (float)gWindow->getSize().y});
        sf::Vector2f playerPos = entity.GetPos();
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

void gameInput(sf::Event e)
{
    switch (e.type)
    {
    case sf::Event::EventType::KeyPressed:
        if (e.key.code == sf::Keyboard::Space)
            space = true;
        if (e.key.code == sf::Keyboard::B)
            CreateEnemy();
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

void gameUpdate()
{
    player.Update();
    player.Move(xAxis, yAxis);
    player.Shoot(space);
    //PushEngineParticules();
    CameraFollow(player.entity);

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
    //renderEngineParticules();
    // RenderShoot();
    player.Render();
    RenderEnnemies();
    gWindow->draw(*player.entity.sprite);
    //ImGui::Text("Particle count: %d", particlePool.CountParticleAlive());
    /*posDebug(playerClass.facing);
    posDebug(playerClass.position);
    posDebug(playerClass.behind);*/
}

Entity *getPlayer()
{
    return (&player.entity);
}
