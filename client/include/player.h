#pragma once

#include "entity.h"
#include "particles.h"
#include "ammunition.h"

extern bool space;
extern float xAxis, yAxis;
extern bool up, down, left, right, shift;

class Player
{
public:
    Entity entity;
    Projectiles projectile;
    ParticleSystem particleSystem;

    Player(){};
    Player(const char *path) {
        projectile.ownedByPlayer = true;
        entity = Entity(path);
        entity.SetPosition({3840 / 2, 2160 / 2});

    }

    void Update() {
        particleSystem.Update(entity, 0, 0, xAxis, yAxis, sf::Color(255, 240, 0, 130), sf::Color(255, 0, 0, 0), 10);
        this->Move(xAxis, yAxis);
        this->Shoot(space);
    }

    void Render(sf::RenderWindow &window) {
        projectile.RenderShoot(window);
        particleSystem.Render(window);
        window.draw(*this->entity.sprite);
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
            projectile.PlayerShoot(&this->entity, "assets/256px/Laser_Large_png_processed.png");
        }
    }
};