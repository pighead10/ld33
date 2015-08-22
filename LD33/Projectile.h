#pragma once

#include "Entity.h"

class ParticleEngine;

class Projectile : public Entity{
public:
	Projectile(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, std::string spriteName, sfld::Vector2f position,
		sfld::Vector2f direction, float speed, ParticleEngine* particleEngine, ENTITY_TYPE target,int damage);
	void update(int frameTime);
	void collided(Entity* other);
private:
	int damage_;
	ENTITY_TYPE target_;
	float speed_;
	sfld::Vector2f direction_;
	ParticleEngine* particleEngine_;
};