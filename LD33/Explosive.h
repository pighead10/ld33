#pragma once

#include "Entity.h"

class ParticleEngine;

class Explosive : public Entity{
public:
	Explosive(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f position,ParticleEngine* particleEngine);
	void collided(Entity* other);
private:
	ParticleEngine* particleEngine_;
};