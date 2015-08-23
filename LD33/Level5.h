#pragma once

#include "Level.h"

class Level5 : public Level{
public:
	explicit Level5(sf::Font* font);
	void startLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine);
};