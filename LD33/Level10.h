#pragma once

#include "Level.h"

class Level10 : public Level{
public:
	explicit Level10(sf::Font* font);
	void startLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine);
};