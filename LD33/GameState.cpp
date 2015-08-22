#include "stdafx.h"
#include "GameState.h"
#include "StateManager.h"
#include "EntityManager.h"
#include "Player.h"
#include "Wall.h"
#include "Guard.h"

GameState::GameState() = default;
GameState::~GameState() = default;

void GameState::sfmlEvent(sf::Event evt){
	if (evt.type == sf::Event::Closed){
		getParent().pop();
	}
}

void GameState::start(){
	entityManager_ = std::unique_ptr<EntityManager>(new EntityManager());

	resourceManager_.setDirectory("media/images/");
	resourceManager_.load("player", "test.png");
	resourceManager_.load("wall", "wall.png");
	resourceManager_.load("guard", "guard.png");
	resourceManager_.load("guard_alert", "guard_alert.png");
	Player* player = new Player(&resourceManager_, entityManager_.get(), sfld::Vector2f(100, 100));
	entityManager_->addEntity(player);
	for (int i = 10; i <= 20; i++){
		entityManager_->addEntity(new Wall(&resourceManager_, entityManager_.get(), sfld::Vector2f(i * TILE_SIZE, 10 * TILE_SIZE)));
		
	}
	entityManager_->addEntity(new Guard(&resourceManager_, entityManager_.get(), sfld::Vector2f(15 * TILE_SIZE, 15 * TILE_SIZE), player));
}

void GameState::pause(){
}

void GameState::resume(){
}

void GameState::exit(){
}

void GameState::update(int frameTime){
	entityManager_->update(frameTime);
}

void GameState::render(sf::RenderTarget* target){
	entityManager_->render(target);
}