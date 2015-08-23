#include "stdafx.h"
#include "Level9.h"
#include "EntityManager.h"
#include "ParticleEngine.h"
#include "Guard.h"
#include "SwitchBlock.h"
#include "stdafx.h"
#include "Switch.h"
#include "SwitchBlock.h"

Level9::Level9(sf::Font* font){
	levelnum_ = 9;
	constructLevel(font);
}

void Level9::startLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine){
	
	baseStartLevel(entityManager, resourceManager, particleEngine);
	guard_limit_ = 4;

	entityManager_->clear();
	particleEngine_->clear();

	loadFromImage("level9");

	std::vector<std::pair<sfld::Vector2f, int>> dirList1;
	dirList1.push_back(std::make_pair(sfld::Vector2f(-1, 0), 500));
	dirList1.push_back(std::make_pair(sfld::Vector2f(1, 0), 500));

	std::vector<std::pair<sfld::Vector2f, int>> dirList2;
	dirList2.push_back(std::make_pair(sfld::Vector2f(1, 0), 2000));
	dirList2.push_back(std::make_pair(sfld::Vector2f(-1, 0), 2000));

	std::vector<std::pair<sfld::Vector2f, int>> dirList3;
	dirList3.push_back(std::make_pair(sfld::Vector2f(0, 1), 1500));
	dirList3.push_back(std::make_pair(sfld::Vector2f(0, -1), 1500));

	std::vector<std::pair<sfld::Vector2f, int>> dirList4;
	dirList4.push_back(std::make_pair(sfld::Vector2f(0, -1), 1500));
	dirList4.push_back(std::make_pair(sfld::Vector2f(-1, 0), 500));
	dirList4.push_back(std::make_pair(sfld::Vector2f(0, 1), 1500));
	dirList4.push_back(std::make_pair(sfld::Vector2f(1, 0), 500));

	std::vector<SwitchBlock*> list1;
	std::vector<SwitchBlock*> list2;
	for (int x = 6; x <= 11; x++){
		SwitchBlock* block1 = new SwitchBlock(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(x, 18)));
		entityManager_->addEntity(block1);
		list1.push_back(block1);
	}

	for (int y = 2; y <= 4; y++){
		SwitchBlock* block = new SwitchBlock(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(25, y)));
		entityManager_->addEntity(block);
		list2.push_back(block);
	}

	Switch* sw = new Switch(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(6,7)), list1, player_);
	entityManager_->addEntity(sw);
	
	Switch* sw2 = new Switch(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(2, 15)), list2, player_);
	entityManager_->addEntity(sw2);

	//entityManager_->addEntity(new Guard(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(28,23)), player_, particleEngine, dirList4));
	//entityManager_->addEntity(new Guard(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(10,11)), player_, particleEngine, dirList3));
	entityManager_->addEntity(new Guard(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(22,4)), player_, particleEngine, dirList2));
	entityManager_->addEntity(new Guard(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(27,2)), player_, particleEngine, dirList1));
	displayMessage("Good luck!");
}