#include "particules.h"

std::vector<Particule *> Particules;

Particule *createParticules()
{
    Particule *part = new Particule();

    part->rect = getPlayer()->GetRect();
    part->color.r = 255;
    part->color.g = 225;
    part->color.b = 0;
    part->color.a = 240;

    part->triangle[0].position = sf::Vector2f(part->rect.left + 20, part->rect.top + part->rect.height / 2 - 5);
    part->triangle[1].position = sf::Vector2f(part->rect.left + part->rect.width - 20, part->rect.top + part->rect.height / 2 - 5);
    part->triangle[2].position = sf::Vector2f(part->rect.left + part->rect.width / 2, part->rect.top + part->rect.height - 25);
    // define the color of the part->triangle's points
    part->triangle[0].color = sf::Color{part->color.r, part->color.g, part->color.b, part->color.a};
    part->triangle[1].color = sf::Color{part->color.r, part->color.g, part->color.b, part->color.a};
    part->triangle[2].color = sf::Color{part->color.r, part->color.g, part->color.b, part->color.a};

    return (part);
}

void pushPart()
{
    //static int time = 0;
    //if (time == 0) {
    //    time = gWindow->elapsed_ms;
    //} else if (gWindow->elapsed_ms - time > 10) {
        Particules.push_back(createParticules());
    //    time = 0;
    //}
}

void renderParticules()
{

    for (int i = 0; i < Particules.size(); i++) {
        // define the position of the triangle's points

        gWindow->draw(Particules[i]->triangle);

        Particules[i]->color.a -= 12;
        printf("%zd || a: %d\n", Particules.size(), Particules[i]->color.a);

        if (Particules[i]->color.a <= 0)
            Particules.erase(Particules.begin() + i);
    }

}

void engineParticules()
{
    renderParticules();
}