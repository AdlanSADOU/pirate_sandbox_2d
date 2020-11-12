/*#include "particle.h"

Particle::Particle():life(0) { }

void Particle::Init(sf::Vector2f pos, float speed, sf::Vector2f direction, sf::Vector2f randomDirection, float size, unsigned int life, sf::Color startColor, sf::Color endColor, sf::BlendMode blendMode)
{
	// Movement properties
	pState.pLive.pos = pos;

	// Life properties
	this->life = pState.pLive.startLife = life;
	pState.pLive.size = size;
	pState.pLive.speed = speed;
	pState.pLive.direction = direction;
	pState.pLive.randomDirection = randomDirection;
	pState.pLive.t = 0.0f;

	// Color properties
	pState.pLive.startColor = startColor;
	pState.pLive.endColor = endColor;
	pState.pLive.blendMode = blendMode;
}

void Particle::Update()
{
	// Calculates new particle position.
	CalculateParticlePos();

	// Decrementing particle life
	life--;
}

bool Particle::Draw(sf::RenderWindow *gWindow)
{
	bool ret = true;

	// Color interpolation, only if the particle has enough life
	sf::Color resColor;

	if (pState.pLive.startLife > MIN_LIFE_TO_INTERPOLATE)
		resColor = RgbInterpolation(pState.pLive.startColor, pState.pLive.t, pState.pLive.endColor);

	// Draw
	sf::VertexArray triangle = sf::VertexArray(sf::Triangles, 3);
	triangle[0].position = sf::Vector2f(this->pState.pLive.pos.x - this->pState.pLive.size, this->pState.pLive.pos.y - this->pState.pLive.size);
    triangle[1].position = sf::Vector2f(this->pState.pLive.pos.x + this->pState.pLive.size, this->pState.pLive.pos.y - this->pState.pLive.size);
    triangle[2].position = sf::Vector2f(this->pState.pLive.pos.x, this->pState.pLive.pos.y + this->pState.pLive.size);
	triangle[0].color = resColor;
    triangle[1].color = resColor;
    triangle[2].color = resColor;
	gWindow->draw(triangle);

	// Time step increment to interpolate colors
	pState.pLive.t += (1.0f / (float)pState.pLive.startLife);

	if (pState.pLive.t >= 1.0f)
		pState.pLive.t = 0.0f;

	return (ret);
}

bool Particle::IsAlive()
{
	return (life > 0);
}

Particle* Particle::GetNext()
{
	return (pState.next);
}

void Particle::SetNext(Particle* next)
{
	pState.next = next;
}

sf::Color Particle::RgbInterpolation(sf::Color startColor, float timeStep, sf::Color endColor)
{
	sf::Color finalColor;

	finalColor.r = startColor.r + (endColor.r - startColor.r) * timeStep;
	finalColor.g = startColor.g + (endColor.g - startColor.g) * timeStep;
	finalColor.b = startColor.b + (endColor.b - startColor.b) * timeStep;
	finalColor.a = startColor.a + (endColor.a - startColor.a) * timeStep;

	return (finalColor);
}

void Particle::CalculateParticlePos()
{
	pState.pLive.pos.x += pState.pLive.direction.x * pState.pLive.randomDirection.x * pState.pLive.speed;
	pState.pLive.pos.y += pState.pLive.direction.y * pState.pLive.randomDirection.y * pState.pLive.speed;
}*/