#include "stdafx.h"
#include "Level6.h"
#include "EntityManager.h"
#include "ParticleEngine.h"
#include "Guard.h"
#include "SwitchBlock.h"
#include "Switch.h"

Level6::Level6(sf::Font* font){
	levelnum_ = 6;
	constructLevel(font);
}

void Level6::sfmlEvent(sf::Event evt){
	baseEvents(evt);
}

void Level6::startLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine){
	
	baseStartLevel(entityManager, resourceManager, particleEngine);
	guard_limit_ = 1;

	entityManager_->clear();
	particleEngine_->clear();

	loadFromImage("level6");

	std::vector<std::pair<sfld::Vector2f, int>> dirList;
	dirList.push_back(std::make_pair(sfld::Vector2f(0, 1), 1000));
	dirList.push_back(std::make_pair(sfld::Vector2f(0, -1), 1000));

	std::vector<SwitchBlock*> switchlist;
	for (int x = 11; x <= 13; x++){
		SwitchBlock* block = new SwitchBlock(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(x, 10)));
		//SwitchBlock* block2 = new SwitchBlock(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(x, 9)));
		switchlist.push_back(block);
		//switchlist.push_back(block2);
		entityManager_->addEntity(block);
		//entityManager_->addEntity(block2);
	}

	entityManager_->addEntity(new Switch(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(3, 14)), switchlist, player_));

	entityManager_->addEntity(new Guard(resourceManager, entityManager,EntityManager::convertCoords(sfld::Vector2f(11,6)), player_, particleEngine, dirList));
}