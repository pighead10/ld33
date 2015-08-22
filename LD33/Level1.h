#pragma once

#include "Level.h"

class Level1 : public Level{
public:
	void sfmlEvent(sf::Event evt);
	void startLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine);
};