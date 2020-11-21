#pragma once

#include "entity.h"
#include "particles.h"
#include "ammunition.h"
#include "imgui-common.h"

extern bool space;
extern float xAxis, yAxis;
extern bool up, down, left, right, shift;
extern sf::RenderWindow *window;

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
        utils::posDebug(this->entity.behind, *window);
        utils::posDebug(this->entity.behind_far, *window);
        utils::posDebug(this->entity.facing, *window);
        this->Move(xAxis, yAxis);
        particleSystem.Update(entity, 0, 0, xAxis, yAxis, sf::Color(255, 240, 0, 130), sf::Color(255, 0, 0, 0), 10);
        this->Shoot(space);
    }

    void Render(sf::RenderWindow &window) {
        projectile.RenderShoot(window);
        particleSystem.Render(window);
        window.draw(*this->entity.sprite);
    }

    void Move(float x, float y) {
        entity.up = up;
        entity.down = down;
        entity.right = right;
        entity.left = left;

        entity.Move(x, y);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(*window);
            mousePosition = window->mapPixelToCoords((sf::Vector2i)mousePosition);
            entity.RotateSpritePoint(mousePosition.x, mousePosition.y, -90);
        }
        else
            entity.RotateSpriteDirection(x, y, 90);
    }

    void Shoot(bool key) {
        if (key) {
            projectile.PlayerShoot(&this->entity, "assets/256px/Laser_Large_png_processed.png");
        }
    }
};