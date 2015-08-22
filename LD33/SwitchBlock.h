#pragma once

#include "Entity.h"

class Player;

class SwitchBlock : public Entity{
public:
	SwitchBlock(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f position);
	void change();
private:
	bool enabled_;
};