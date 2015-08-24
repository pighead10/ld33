#include "stdafx.h"
#include "Level4.h"
#include "Guard.h"
#include "EntityManager.h"

Level4::Level4(sf::Font* font){
	levelnum_ = 4;
	constructLevel(font);
}

void Level4::startLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine){
	
	baseStartLevel(entityManager, resourceManager, particleEngine);
	loadFromImage("level4");
	displayMessage("Time your transformations!");
	guard_limit_ = 2;

	std::vector<std::pair<sfld::Vector2f, int>> dirList;
	dirList.push_back(std::make_pair(sfld::Vector2f(0, 1), 2000));
	dirList.push_back(std::make_pair(sfld::Vector2f(0, -1), 2000));
	entityManager_->addEntity(new Guard(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(18, 3)), player_, particleEngine, dirList));
}