#include "stdafx.h"
#include "Level7.h"
#include "EntityManager.h"
#include "ParticleEngine.h"
#include "Guard.h"
#include "SwitchBlock.h"
#include "stdafx.h"
#include "Switch.h"
#include "SwitchBlock.h"

Level7::Level7(sf::Font* font){
	levelnum_ = 7;
	constructLevel(font);
}

void Level7::sfmlEvent(sf::Event evt){
	baseEvents(evt);
}

void Level7::startLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine){
	
	baseStartLevel(entityManager, resourceManager, particleEngine);
	guard_limit_ = 0;

	entityManager_->clear();
	particleEngine_->clear();

	loadFromImage("level7");

	std::vector<std::pair<sfld::Vector2f, int>> dirList;
	dirList.push_back(std::make_pair(sfld::Vector2f(1, 0), 2500));
	dirList.push_back(std::make_pair(sfld::Vector2f(-1, 0), 2500));

	std::vector<SwitchBlock*> list;
	for (int x = 0; x <= 10; x++){
		SwitchBlock* block1 = new SwitchBlock(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(x, 9)));
		entityManager_->addEntity(block1);
		list.push_back(block1);

		SwitchBlock* block2 = new SwitchBlock(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(x, 13)));
		entityManager_->addEntity(block2);
		list.push_back(block2);
	}
	for (int y = 9; y <= 13; y++){
		SwitchBlock* block = new SwitchBlock(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(10, y)));
		entityManager_->addEntity(block);
		list.push_back(block);
	}

	Switch* sw = new Switch(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(9,11)),list,player_);
	entityManager_->addEntity(sw);
	sw->change();


	entityManager_->addEntity(new Guard(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(0,8)), player_, particleEngine, dirList));
	entityManager_->addEntity(new Guard(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(0, 14)), player_, particleEngine, dirList));
	displayMessage("Can you dodge bullets?");
}