#include "stdafx.h"
#include "Level5.h"
#include "Guard.h"
#include "EntityManager.h"
#include "SwitchBlock.h"
#include "Switch.h"

Level5::Level5(sf::Font* font){
	constructLevel(font);
}

void Level5::startLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine){
	baseStartLevel(entityManager, resourceManager, particleEngine);
	loadFromImage("level5");
	displayMessage("Look! Button!");
	guard_limit_ = 1;

	std::vector<SwitchBlock*> list;
	for (int y = 11; y <= 13; y++){
		SwitchBlock* block = new SwitchBlock(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(6, y)));
		list.push_back(block);
		entityManager_->addEntity(block);
	}

	for (int y = 9; y <= 13; y++){
		if (y != 11){
			SwitchBlock* block = new SwitchBlock(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(10, y)));
			list.push_back(block);
			entityManager_->addEntity(block);
		}
	}
	Switch* sw = new Switch(resourceManager, entityManager, EntityManager::convertCoords(sfld::Vector2f(10, 11)), list, player_);
	entityManager_->addEntity(sw);
	sw->change();
}