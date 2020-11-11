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

    EnnemyType *ennemy = (EnnemyType *)malloc(sizeof(EnnemyType));
    ennemy->entity = new Entity("assets/256px/Enemy02_Teal_Frame_1_png_processed.png");
    // ennemy->speed = rand() % 10 + 1;
    ennemy->speed = 3;
    ennemy->dead = 0;
    ennemy->hp = 100;
    ennemy->direction = GetRandomNormalizedVector();
    ennemy->entity->SetPosition(sf::Vector2f{1500, 1000});
    ennemy->position = sf::Vector2f{1500, 1000};
    ennemy->entity->RotateSprite(ennemy->direction.x, ennemy->direction.y, 270);
    ennemy->lifeClock.restart();

    return (ennemy);
}

void PushEnemy()
{
    Ennemies.push_back(CreateEnemy());
}


void UpdatePosition(EnnemyType *ennemy)
{
    sf::Time time = ennemy->clock.getElapsedTime();

    if (time.asSeconds() > 0.01f) {
        ennemy->entity->Move(ennemy->direction.x * ennemy->speed, ennemy->direction.y * ennemy->speed);
        ennemy->clock.restart();
    }
}

void FreeEnemy(EnnemyType *ennemy, int index)
{
    ennemy->entity->FreeEntity();
    free(ennemy);
    Ennemies.erase(Ennemies.begin() + index);
}

void UpdateEnnemy(EnnemyType *ennemy, int index)
{
    sf::Time ammoLifeTime = ennemy->lifeClock.getElapsedTime();
    UpdatePosition(ennemy);

    if (Ennemies.size() > 0) {
        if (ammoLifeTime.asSeconds() > 30.0f || ennemy->dead == 1) {
            FreeEnemy(ennemy, index);
        }
    }
}

void FreeEnnemies()
{

}

std::vector<EnnemyType *> GetEnnemies()
{
    return (Ennemies);
}

void RenderEnnemies()
{
    for (int i = 0; i < Ennemies.size(); i++) {
        gWindow->draw(*Ennemies[i]->entity->sprite);
        UpdateEnnemy(Ennemies[i], i);
    }
    ImGui::Text("Mobs count: %d\n", Ennemies.size());
}