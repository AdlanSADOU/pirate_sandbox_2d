#include "enemy.h"

// definitions in cpp file

std::vector<EnnemyType *> Ennemies;

sf::Vector2f GetRandomNormalizedVector()
{
    float randX = (-1.0f + float(rand() % 200 / 100.0f));
    float randY = (-1.0f + float(rand() % 200 / 100.0f));

    return (sf::Vector2f(randX, randY));
}

EnnemyType *CreateEnemy()
{
    Entity *playerClass = getPlayer();

    //Init
    EnnemyType *ennemy = (EnnemyType *)malloc(sizeof(EnnemyType));
    ennemy->entity = new Entity("assets/256px/Enemy02_Teal_Frame_1_png_processed.png");

    //Explosion
    ennemy->explosionRect = sf::IntRect(0, 0, 120, 120);
    ennemy->explosion = new Entity("assets/256px/explosion.png", ennemy->explosionRect);
    ennemy->explosion->SetPosition(sf::Vector2f{1500, 1000});
    // ennemy->explosion->sprite->getTextureRect();


    //Common attributes
    ennemy->speed = rand() % 7 + 1;
    ennemy->dead = 0;
    ennemy->hp = 100;
    ennemy->direction = GetRandomNormalizedVector();
    ennemy->entity->SetPosition(sf::Vector2f{1500, 1000});
    ennemy->entity->RotateSprite(ennemy->direction.x, ennemy->direction.y, 270);
    ennemy->lifeClock.restart();
    ennemy->explosionClock.restart();

    return (ennemy);
}

void PushEnemy()
{
    Ennemies.push_back(CreateEnemy());
}

void MoveExplosionRect(EnnemyType *ennemy)
{
    sf::Time time = ennemy->explosionClock.getElapsedTime();

    if (ennemy->explosionRect.left < 960 && time.asSeconds() > 0.1) {
        ennemy->explosionRect.left += 120;
        ennemy->explosionClock.restart();
    }
    else {
        ennemy->dead = 2;
    }
}

void UpdatePosition(EnnemyType *ennemy)
{
    sf::Time time = ennemy->clock.getElapsedTime();

    // if (time.asSeconds() > 0.01f && ennemy->dead != 1) {
    //     ennemy->entity->Move(ennemy->direction.x * ennemy->speed, ennemy->direction.y * ennemy->speed);
    //     ennemy->explosion->Move(ennemy->direction.x * ennemy->speed, ennemy->direction.y * ennemy->speed);
    //     ennemy->clock.restart();
    // }

    // if (ennemy->dead == 1) {
    //     MoveExplosionRect(ennemy);
    // }
}

void FreeEnemy(EnnemyType *ennemy, int index)
{
    ennemy->entity->FreeEntity();
    free(ennemy);
    Ennemies.erase(Ennemies.begin() + index);
}

void UpdateEnnemy(EnnemyType *ennemy, int index)
{
    sf::Time ennemyLifeTime = ennemy->lifeClock.getElapsedTime();
    UpdatePosition(ennemy);

    if (Ennemies.size() > 0) {
        if (ennemyLifeTime.asSeconds() > 30.0f || ennemy->dead == 2) {
            FreeEnemy(ennemy, index);
        }
    }
}

std::vector<EnnemyType *> GetEnnemies()
{
    return (Ennemies);
}

void RenderEnnemies()
{
    for (int i = 0; i < Ennemies.size(); i++) {

        // // Ennemies[i]->explosion->sprite->setOrigin(0,0);

        // // Ennemies[i]->entity->sprite->setOrigin({0.0f, 0.0f});

        // sf::RectangleShape rectangle;
        // rectangle.setSize(sf::Vector2f(Ennemies[i]->explosionRect.width, Ennemies[i]->explosionRect.height));
        // rectangle.setOutlineColor(sf::Color::Red);
        // rectangle.setOutlineThickness(5);
        // rectangle.setOrigin(sf::Vector2f{0,0});
        // sf::Vector2f pos = Ennemies[i]->explosion->sprite->getPosition();
        // rectangle.setPosition(pos.x, pos.y);

        // sf::RectangleShape entRectangle;
        // entRectangle.setSize(sf::Vector2f(Ennemies[i]->entity->sprite->getTextureRect().width, Ennemies[i]->entity->sprite->getTextureRect().height));
        // entRectangle.setOutlineColor(sf::Color::Blue);
        // entRectangle.setOutlineThickness(5);
        // sf::Vector2f entPos = Ennemies[i]->entity->sprite->getPosition();
        // entRectangle.setPosition(entPos.x, entPos.y);


        // gWindow->draw(rectangle);
        // gWindow->draw(entRectangle);
        // if (Ennemies[i]->dead == 1) {
            gWindow->draw(*Ennemies[i]->explosion->sprite);
        // }
        // else {
            gWindow->draw(*Ennemies[i]->entity->sprite);
        // }
        UpdateEnnemy(Ennemies[i], i);
    }
    ImGui::Text("Mobs count: %d\n", Ennemies.size());
}