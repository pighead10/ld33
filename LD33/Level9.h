#pragma once

#include "Level.h"

class Level9 : public Level{
public:
	explicit Level9(sf::Font* font);
	void startLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine);
};