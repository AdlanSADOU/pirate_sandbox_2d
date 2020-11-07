#include "enemy.h"

// definitions in cpp file

void Enemy::DrawEnemy()
{
    Enemy::entity.Draw(false);
}

void Enemy::MovePosition(float x, float y)
{
    Enemy::entity.Move(x, y);
}