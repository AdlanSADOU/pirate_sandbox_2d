/*#include "particlepool.h"
#include <assert.h>

// This pool constructor sets our particles to available
ParticlePool::ParticlePool()
{
	// Fill the pool according to poolSize needed for the emitter
	poolSize = 100000;
	particleArray = new Particle[poolSize];

	// The first particle is available
	firstAvailable = &particleArray[0];

	// Each particle points to the next one
	for (int i = 0; i < poolSize - 1; i++)
		particleArray[i].SetNext(&particleArray[i + 1]);

	// The last particle points to nullptr indicating the end of the vector
	particleArray[poolSize - 1].SetNext(nullptr);
}

int ParticlePool::GetPoolSize()
{
	return (this->poolSize);
}

int ParticlePool::CountParticleAlive()
{
	int count = 0;
	for (int i = 0; i < GetPoolSize(); i++)
		if (particleArray[i].IsAlive() == true)
			count++;
	return (count);
}

void ParticlePool::FreeParticlePool()
{
	delete[] particleArray;
	particleArray = nullptr;
}

void ParticlePool::Generate(sf::Vector2f pos, float speed, sf::Vector2f direction, sf::Vector2f randomDirection, float size, unsigned int life, sf::Color startColor, sf::Color endColor, sf::BlendMode blendMode)
{
	// Check if the pool is not full
	assert(firstAvailable != nullptr);

	// Remove it from the available list
	Particle* newParticle = firstAvailable;
	firstAvailable = newParticle->GetNext();

	// Initialize new alive particle
	newParticle->Init(pos, speed, direction, randomDirection, size, life, startColor, endColor, blendMode);
}

ParticleState ParticlePool::Update(sf::RenderWindow *gWindow)
{
	ParticleState retState = ParticleState::PARTICLE_STATE_NOT_DEF;

	for (int i = 0; i < poolSize; i++)
	{
		if (particleArray[i].IsAlive())
		{
			particleArray[i].Update();

			if (particleArray[i].Draw(gWindow))
				retState = ParticleState::PARTICLE_ALIVE_DRAWN;
			else
				retState = ParticleState::PARTICLE_ALIVE_NOT_DRAWN;
		}
		else // if a particle dies it becomes the first available in the pool
		{
			// Add this particle to the front of the vector
			particleArray[i].SetNext(firstAvailable);
			firstAvailable = &particleArray[i];
			retState = ParticleState::PARTICLE_DEAD;
		}
	}

	return (retState);
}*/