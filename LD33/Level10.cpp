#include "stdafx.h"
#include "Level10.h"
#include "EntityManager.h"
#include "ParticleEngine.h"
#include "Guard.h"
#include "SwitchBlock.h"
#include "stdafx.h"
#include "Switch.h"
#include "SwitchBlock.h"

Level10::Level10(sf::Font* font){
	constructLevel(font);
}

void Level10::startLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine){
	baseStartLevel(entityManager, resourceManager, particleEngine);
	guard_limit_ = 3;

	entityManager_->clear();
	particleEngine_->clear();

	loadFromImage("level10");

	std::vector<std::pair<sfld::Vector2f, int>> dirList1;
	dirList1.push_back(std::make_pair(sfld::Vector2f(0, 1), 4000));
	dirList1.push_back(std::make_pair(sfld::Vector2f(0, -1), 4000));

	std::vector<std::pair<sfld::Vector2f, int>> dirList2;
	dirList2.push_back(std::make_pair(sfld::Vector2f(0, -1), 6000));
	dirList2.push_back(std::make_pair(sfld::Vector2f(0, 1), 6000)); //TIMELAPSE!

	std::vector<SwitchBlock*> list1;
	std::vector<SwitchBlock*> list2;
	for (int x = 7; x <= 17; x++){
		SwitchBlock* block1 = new SwitchBlock(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(x, 2)));
		entityManager_->addEntity(block1);
		list1.push_back(block1);
	}

	for (int x= 7; x <= 17; x++){
		SwitchBlock* block = new SwitchBlock(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(x, 5)));
		entityManager_->addEntity(block);
		list2.push_back(block);
	}

	Switch* sw = new Switch(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(8,0)), list1, player_);
	entityManager_->addEntity(sw);

	Switch* sw2 = new Switch(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(16, 0)), list2, player_);
	entityManager_->addEntity(sw2);

	//entityManager_->addEntity(new Guard(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(28,23)), player_, particleEngine, dirList4));
	//entityManager_->addEntity(new Guard(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(10,11)), player_, particleEngine, dirList3));
	entityManager_->addEntity(new Guard(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(21, 0)), player_, particleEngine, dirList1));
	entityManager_->addEntity(new Guard(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(31, 23)), player_, particleEngine, dirList2));
	//entityManager_->addEntity(new Guard(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(27, 2)), player_, particleEngine, dirList1));
	displayMessage("Save a life!");
}