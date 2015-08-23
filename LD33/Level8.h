#pragma once

#include "Level.h"

class Level8 : public Level{
public:
	explicit Level8(sf::Font* font);
	void startLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine);
};