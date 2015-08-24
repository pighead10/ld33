#include "stdafx.h"
#include "Level2.h"

Level2::Level2(sf::Font* font){
	levelnum_ = 2;
	constructLevel(font);
}

void Level2::startLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine){
	
	baseStartLevel(entityManager, resourceManager, particleEngine);
	loadFromImage("level2");
	displayMessage("Don't get seen as a Crythrope!");
	guard_limit_ = 0;
}