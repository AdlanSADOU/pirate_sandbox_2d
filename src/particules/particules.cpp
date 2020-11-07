#include "particules.h"

std::vector<Particule *> Particules1;

Particule *createParticules()
{
    Particule *part = (Particule *)malloc(sizeof(Particule));

    part->rect = (S2D_FRect)getPlayer()->GetRect();
    part->color.r = 1.0f;
    part->color.g = 0.9f;
    part->color.b = 0.0f;
    part->color.a = 0.9f;
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
    for (int i = 0; i < Particules.size(); i++) {
        S2D_DrawTriangle(Particules[i]->rect.x + 20, Particules[i]->rect.y + Particules[i]->rect.height / 2 - 5, Particules[i]->color.r, Particules[i]->color.g, Particules[i]->color.b, Particules[i]->color.a,
                         Particules[i]->rect.x + Particules[i]->rect.width - 20, Particules[i]->rect.y + Particules[i]->rect.height / 2 - 5, Particules[i]->color.r, Particules[i]->color.g, Particules[i]->color.b, Particules[i]->color.a,
                         Particules[i]->rect.x + Particules[i]->rect.width / 2, Particules[i]->rect.y + Particules[i]->rect.height - 25, Particules[i]->color.r, Particules[i]->color.g, Particules[i]->color.b, Particules[i]->color.a);
        Particules[i]->color.a -= 0.03f;
        Particules[i]->color.r -= 0.015f;
        Particules[i]->color.g -= 0.025f;
        if (Particules[i]->color.a <= 0.0f)
            Particules.erase(Particules.begin() + i + 1);
    }
}

void engineParticules()
{
    renderParticules(Particules1);
}