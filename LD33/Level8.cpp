#include "stdafx.h"
#include "Level8.h"

Level8::Level8(sf::Font* font){
	constructLevel(font);
}

void Level8::startLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine){
	baseStartLevel(entityManager, resourceManager, particleEngine);
	loadFromImage("level8");
	displayMessage("TNT explodes when shot!");
	guard_limit_ = 4;
}