#include "stdafx.h"
#include "GameState.h"
#include "StateManager.h"
#include "EntityManager.h"
#include "ParticleEngine.h"
#include "Level.h"
#include "Level1.h"

GameState::GameState() = default;
GameState::~GameState() = default;

void GameState::sfmlEvent(sf::Event evt){
	if (currentLevel_ != NULL){
		currentLevel_->sfmlEvent(evt);
	}
	if (evt.type == sf::Event::Closed){
		getParent().pop();
	}
}

void GameState::start(){
	currentLevel_ = NULL;
	entityManager_ = std::unique_ptr<EntityManager>(new EntityManager());
	particleEngine_ = std::unique_ptr<ParticleEngine>(new ParticleEngine());

	resourceManager_.setDirectory("media/images/");
	resourceManager_.load("player", "test.png");
	resourceManager_.load("player_monster", "player_monster.png");
	resourceManager_.load("wall", "wall.png");
	resourceManager_.load("guard", "guard.png");
	resourceManager_.load("guard_alert", "guard_alert.png");
	resourceManager_.load("projectile", "bullet.png");
	resourceManager_.load("switch_on", "switch_on.png");
	resourceManager_.load("switch_off", "switch_off.png");
	resourceManager_.load("switchblock_on", "switchblock_on.png");
	resourceManager_.load("switchblock_off", "switchblock_off.png");
	resourceManager_.load("samplelevel", "levels/samplelevel.png");
	resourceManager_.load("serum", "serum.png");
	resourceManager_.load("player_attacking", "player_attacking.png");

	levels_.push_back(std::unique_ptr<Level>(new Level1()));
	levelnum_ = -1;
	advanceLevel();
}

void GameState::advanceLevel(){
	levelnum_++;
	if (levelnum_ < levels_.size()){
		currentLevel_ = levels_[levelnum_].get();
		currentLevel_->startLevel(entityManager_.get(), &resourceManager_, particleEngine_.get());
	}
	else{
		std::cout << "No more levels!" << std::endl;
	}
}

void GameState::pause(){
}

void GameState::resume(){
}

void GameState::exit(){
}

void GameState::update(int frameTime){
	if (currentLevel_ != NULL){
		currentLevel_->update(frameTime);
		if (currentLevel_->getAdvanceLevel()){
			advanceLevel();
		}
	}
}

void GameState::render(sf::RenderTarget* target){
	if (currentLevel_ != NULL){
		currentLevel_->render(target);
	}
}