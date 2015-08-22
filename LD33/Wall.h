#pragma once

#include "Entity.h"

class Wall : public Entity{
public:
	Wall(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager,sfld::Vector2f position);
};