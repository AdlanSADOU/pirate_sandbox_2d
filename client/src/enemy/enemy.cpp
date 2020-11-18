#include "enemy.h"

// definitions in cpp file

std::vector<EnnemyType *> Ennemies;

EnnemyType *PushEnnemy()
{
    //Init
    EnnemyType *ennemy = (EnnemyType *)malloc(sizeof(EnnemyType));
    ParticleSystem *tmpParticleSystem = new ParticleSystem();
    Projectiles *tmpProjectiles = new Projectiles();

    ennemy->entity = new Entity("assets/256px/Enemy02_Teal_Frame_1_png_processed.png");

    //Explosion
    ennemy->explosionRect = sf::IntRect(0, 0, 120, 120);
    ennemy->explosion = new Entity("assets/256px/explosion.png", ennemy->explosionRect);
    ennemy->explosion->SetPosition(sf::Vector2f{1500, 1000});
    ennemy->explosion->sprite->setScale(sf::Vector2f(1.5, 1.5));

    //Common attributes
    ennemy->speed = rand() % 7 + 1;
    ennemy->dead = 0;
    ennemy->hp = 100;
    ennemy->direction = utils::GetRandomNormalizedVector();
    ennemy->entity->SetPosition(sf::Vector2f{1500, 1000});
    ennemy->entity->RotateSprite(ennemy->direction.x, ennemy->direction.y, 90);
    ennemy->lifeClock.restart();
    ennemy->explosionClock.restart();
    ennemy->entity->sprite->setScale(sf::Vector2f(-1, -1));

    // Particles & Projectiles
    ennemy->particleSystem = tmpParticleSystem;
    ennemy->projectile = tmpProjectiles;

    //Life and shield bars
    // ennemy->shieldRect = sf::RectangleShape();
    // ennemy->shieldRect.setSize(sf::Vector2f(50, 10));
    // ennemy->shieldRect.setOutlineColor(sf::Color::Red);
    // ennemy->shieldRect.setOutlineThickness(5);
    // ennemy->shieldRect.setPosition(1500, 1000);
    
    return (ennemy);
}

void CreateEnemy()
{
    Ennemies.push_back(PushEnnemy());
}

void MoveExplosionRect(EnnemyType *ennemy)
{
    sf::Time time = ennemy->explosionClock.getElapsedTime();

    if (ennemy->explosionRect.left < 960 && time.asSeconds() > 0.08) {
        ennemy->explosionRect.left += 120;
        ennemy->explosion->sprite->setTextureRect(ennemy->explosionRect);
        ennemy->explosionClock.restart();
    }
    else if (ennemy->explosionRect.left >= 960 && time.asSeconds() > 0.1){
        ennemy->dead = 2;
    }
}

void UpdatePosition(EnnemyType *ennemy)
{
    sf::Time time = ennemy->clock.getElapsedTime();

    if (time.asSeconds() > 0.01f && ennemy->dead != 1) {
        ennemy->entity->Move(ennemy->direction.x * ennemy->speed, ennemy->direction.y * ennemy->speed);
        ennemy->entity->RotateSprite(ennemy->direction.x, ennemy->direction.y, 90);
        ennemy->explosion->Move(ennemy->direction.x * ennemy->speed, ennemy->direction.y * ennemy->speed);
        ennemy->clock.restart();
    }

    if (ennemy->dead == 1) {
        MoveExplosionRect(ennemy);
    }
}

void FreeEnemy(EnnemyType *ennemy, int index)
{
    ennemy->entity->FreeEntity();
    ennemy->explosion->FreeEntity();
    free(ennemy);
    Ennemies.erase(Ennemies.begin() + index);
}

void UpdateEnnemy(EnnemyType *ennemy, int index)
{
    sf::Time ennemyLifeTime = ennemy->lifeClock.getElapsedTime();
    UpdatePosition(ennemy);

    // Update particles & projectiles
    ennemy->particleSystem->Update(*ennemy->entity, 0, 0, 2, 2, sf::Color(0, 255, 255, 130), sf::Color(0, 0, 255, 0), 10);
    ennemy->projectile->PlayerShoot(ennemy->entity, "assets/256px/Minigun_Medium_png_processed.png");

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

void RenderEnnemies(sf::RenderWindow &window)
{
    for (int i = 0; i < Ennemies.size(); i++) {
        if (Ennemies[i]->dead) {
            window.draw(*Ennemies[i]->explosion->sprite);
        }
        else if (!Ennemies[i]->dead) {
            
            // Render particles & projectiles
            Ennemies[i]->particleSystem->Render(window);
            Ennemies[i]->projectile->RenderShoot(window);

            window.draw(*Ennemies[i]->entity->sprite);
            // window.draw(Ennemies[i]->blackRect);
        }
        UpdateEnnemy(Ennemies[i], i);
    }
    ImGui::Text("Mobs count: %d\n", Ennemies.size());
}