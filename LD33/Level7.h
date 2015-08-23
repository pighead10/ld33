#pragma once

#include "Level.h"

class Level7 : public Level{
public:
	explicit Level7(sf::Font* font);
	void sfmlEvent(sf::Event evt);
	void startLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine);
};