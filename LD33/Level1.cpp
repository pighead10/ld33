#include "stdafx.h"
#include "Level1.h"

Level1::Level1(sf::Font* font){
	levelnum_ = 1;
	constructLevel(font);
}

void Level1::startLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine){
	baseStartLevel(entityManager, resourceManager, particleEngine);
	loadFromImage("level1");
	displayMessage("Get the serum!");
	guard_limit_ = 0;
}