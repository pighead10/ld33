#pragma once

#include "Entity.h"

class Guard : public Entity{
public:
	Guard(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f position,Entity* player);
	void update(int frameTime);
private:
	bool alert_;
	Entity* player_;
};