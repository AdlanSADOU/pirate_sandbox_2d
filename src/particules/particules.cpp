#include "particules.h"

std::vector<Particule *> Particules;

Particule *createParticules(int offsetX, int offsetY)
{
    Particule *part = new Particule();

    Entity *playerClass = getPlayer();
    sf::Vector2f playerBack = playerClass->behind;
    sf::Vector2f rotation = playerClass->behind;
    playerBack.x += offsetX;
    playerBack.y += offsetY;
    sf::Uint8 r = 22;
    sf::Uint8 g = 22;
    sf::Uint8 b = 22;
    sf::Uint8 a = 240;

    float s = sin(-0.3f + float(rand() % 60 / 100.0f));
    float c = cos(-0.3f + float(rand() % 60 / 100.0f));
    // translate point back to origin:
    rotation.x -= playerClass->position.x;
    rotation.y -= playerClass->position.y;
    // rotate point
    float xnew = rotation.x * c - rotation.y * s;
    float ynew = rotation.x * s + rotation.y * c;
    // translate point back:
    rotation.x = xnew + playerClass->position.x;
    rotation.y = ynew + playerClass->position.y;

    part->direction = rotation;
    part->triangle[0].position = sf::Vector2f(playerBack.x - 2, playerBack.y - 2);
    part->triangle[1].position = sf::Vector2f(playerBack.x + 2, playerBack.y - 2);
    part->triangle[2].position = sf::Vector2f(playerBack.x, playerBack.y + 2);
    // define the color of the part->triangle's points
    part->triangle[0].color = sf::Color{r, g, b, a};
    part->triangle[1].color = sf::Color{r, g, b, a};
    part->triangle[2].color = sf::Color{r, g, b, a};

    return (part);
}

void pushPart()
{
    //static int time = 0;
    //if (time == 0) {
    //    time = gWindow->elapsed_ms;
    //} else if (gWindow->elapsed_ms - time > 10) {
    for (int i = 0, value = 15; i != 6; i++) {
        Particules.push_back(createParticules(rand() % value, rand() % value));
        Particules.push_back(createParticules(-(rand() % value), -(rand() % value)));
        Particules.push_back(createParticules(rand() % value, -(rand() % value)));
        Particules.push_back(createParticules(-(rand() % value), rand() % value));
        Particules.push_back(createParticules(-(rand() % value), 0));
        Particules.push_back(createParticules(rand() % value, 0));
        Particules.push_back(createParticules(0, rand() % value));
        Particules.push_back(createParticules(0, -(rand() % value)));
    }       
    //    time = 0;
    //}
}

void renderParticules()
{

    for (int i = 0; i < Particules.size(); i++) {

        gWindow->draw(Particules[i]->triangle);

        Particules[i]->triangle[0].color.a -= 12;
        Particules[i]->triangle[1].color.a -= 12;
        Particules[i]->triangle[2].color.a -= 12;
        Particules[i]->triangle[0].color.b += 11;
        Particules[i]->triangle[1].color.b += 11;
        Particules[i]->triangle[2].color.b += 11;
        Particules[i]->triangle[0].color.r += 11;
        Particules[i]->triangle[1].color.r += 11;
        Particules[i]->triangle[2].color.r += 11;
        Particules[i]->triangle[0].color.g += 11;
        Particules[i]->triangle[1].color.g += 11;
        Particules[i]->triangle[2].color.g += 11;

        /*Particules[i]->triangle[0].position.x += Particules[i]->direction.x;
        Particules[i]->triangle[0].position.y += Particules[i]->direction.y;
        Particules[i]->triangle[1].position.x += Particules[i]->direction.x;
        Particules[i]->triangle[1].position.y += Particules[i]->direction.y;
        Particules[i]->triangle[2].position.x += Particules[i]->direction.x;
        Particules[i]->triangle[2].position.y += Particules[i]->direction.y;*/

        if (Particules[i]->triangle[0].color.a <= 0) {
            delete(Particules[i]);
            Particules.erase(Particules.begin() + i);
        }
    }

}

void engineParticules()
{
    renderParticules();
}