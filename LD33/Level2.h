#pragma once

#include "Level.h"

class Level2 : public Level{
public:
	explicit Level2(sf::Font* font);
	void startLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine);
};