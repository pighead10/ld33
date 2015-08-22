#pragma once

#include "Entity.h"

class Serum : public Entity{
public:
	Serum(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f position);
	bool hasCollected() const;
	void collided(Entity* other);
private:
	bool collected_;
};