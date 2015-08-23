#pragma once

#include "Level.h"

class Level4 : public Level{
public:
	explicit Level4(sf::Font* font);
	void startLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine);
};