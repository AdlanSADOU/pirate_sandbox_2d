/*#ifndef __PARTICLE_POOL_H__
#define __PARTICLE_POOL_H__

#include "particle.h"
#include <vector>

enum ParticleState
{
	PARTICLE_STATE_NOT_DEF,
	PARTICLE_ALIVE_DRAWN,
	PARTICLE_ALIVE_NOT_DRAWN,
	PARTICLE_DEAD
};

class ParticlePool
{
private:
	
	int poolSize = 0;
	Particle* firstAvailable;
	Particle* particleArray = nullptr;

public:

	ParticlePool();
	
	void FreeParticlePool();
	int GetPoolSize();
	int CountParticleAlive();

	// Generates a new particle each time it's called
	void Generate(sf::Vector2f pos, float speed, sf::Vector2f direction, sf::Vector2f randomDirection, float size, unsigned int life, sf::Color startColor, sf::Color endColor, sf::BlendMode blendMode);
	
	// Update (move and draw) particles in the pool.
	// IMPORTANT NOTE: This method returns:
	//		- PARTICLE_ALIVE_DRAWN: if the particle is still alive and has been drawn succesfully
	//      - PARTICLE_ALIVE_NOT_DRAWN:  if the particle is alive and has NOT been drawn succesfully
	//		- PARTICLE_DEAD: if is particle is no longer alive

	ParticleState Update(sf::RenderWindow *gWindow);
};

#endif*/