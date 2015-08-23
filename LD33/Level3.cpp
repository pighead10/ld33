#include "stdafx.h"
#include "Level3.h"

Level3::Level3(sf::Font* font){
	constructLevel(font);
}

void Level3::startLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine){
	baseStartLevel(entityManager, resourceManager, particleEngine);
	loadFromImage("level3");
	displayMessage("Slaughter is unavoidable!");
	guard_limit_ = 1;
}