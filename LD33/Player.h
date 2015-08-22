#pragma once

#include "Entity.h"

class Player : public Entity{
public:
	Player(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f position);
	void update(int frameTime);
private:
	float speed_;
};