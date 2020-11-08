#include "particules.h"

std::vector<Particule *> Particules1;

Particule *createParticules()
{
    Particule *part = (Particule *)malloc(sizeof(Particule));

    part->rect = getPlayer()->GetRect();
    part->color.r = 255;
    part->color.g = 225;
    part->color.b = 0;
    part->color.a = 240;
    return (part);
}

void pushPart()
{
    //static int time = 0;
    //if (time == 0) {
    //    time = gWindow->elapsed_ms;
    //} else if (gWindow->elapsed_ms - time > 10) {
        Particules1.push_back(createParticules());
    //    time = 0;
    //}
}

void renderParticules(std::vector<Particule *> Particules)
{
    sf::Vertex triangle[3];

    for (int i = 0; i < Particules.size(); i++) {
        // define the position of the triangle's points
        triangle[0].position = sf::Vector2f(Particules[i]->rect.left + 20, Particules[i]->rect.top + Particules[i]->rect.height / 2 - 5);
        triangle[1].position = sf::Vector2f(Particules[i]->rect.left + Particules[i]->rect.width - 20, Particules[i]->rect.top + Particules[i]->rect.height / 2 - 5);
        triangle[2].position = sf::Vector2f(Particules[i]->rect.left + Particules[i]->rect.width / 2, Particules[i]->rect.top + Particules[i]->rect.height - 25);
        // define the color of the triangle's points
        triangle[0].color = sf::Color{Particules[i]->color.r, Particules[i]->color.g, Particules[i]->color.b, Particules[i]->color.a};
        triangle[1].color = sf::Color{Particules[i]->color.r, Particules[i]->color.g, Particules[i]->color.b, Particules[i]->color.a};
        triangle[2].color = sf::Color{Particules[i]->color.r, Particules[i]->color.g, Particules[i]->color.b, Particules[i]->color.a};

        gWindow->draw(triangle, 3, sf::Triangles);
        Particules[i]->color.a -= 30;
        printf("%d\n", Particules.size());

        Particules.erase(Particules.begin() + i);
    }

}

void engineParticules()
{
    renderParticules(Particules1);
}