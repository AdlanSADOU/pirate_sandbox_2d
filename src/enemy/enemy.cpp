#include "enemy.h"

// definitions in cpp file

void Enemy::DrawEnemy()
{
    Enemy::enemy->Draw(false);
}

void Enemy::MovePosition(float x, float y)
{
    Enemy::enemy->Move(x, y);
}