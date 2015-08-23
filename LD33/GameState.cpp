#include "stdafx.h"
#include "GameState.h"
#include "StateManager.h"
#include "EntityManager.h"
#include "ParticleEngine.h"
#include "Level.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "Level6.h"
#include "Level7.h"
#include "Level8.h"
#include "Level9.h"
#include "Level10.h"

GameState::GameState() = default;
GameState::~GameState() = default;

void GameState::sfmlEvent(sf::Event evt){
	if (currentLevel_ != NULL){
		//if (evt.type == sf::Event::KeyReleased)
		currentLevel_->sfmlEvent(evt);
	}
	if (evt.type == sf::Event::Closed){
		getParent().pop();
	}
}

void GameState::start(){
	font = sf::Font();
	font.loadFromFile("media/victor-pixel.ttf");

	currentLevel_ = NULL;
	entityManager_ = std::unique_ptr<EntityManager>(new EntityManager());
	particleEngine_ = std::unique_ptr<ParticleEngine>(new ParticleEngine());

	resourceManager_.setDirectory("media/images/");
	resourceManager_.load("player", "player.png");
	resourceManager_.load("player_monster", "player_monster.png");
	resourceManager_.load("wall", "wall.png");
	resourceManager_.load("guard", "guard.png");
	resourceManager_.load("guard_alert", "guard_alert.png");
	resourceManager_.load("projectile", "bullet.png");
	resourceManager_.load("switch_on", "switch_on.png");
	resourceManager_.load("switch_off", "switch_off.png");
	resourceManager_.load("switchblock_on", "switchblock_on.png");
	resourceManager_.load("switchblock_off", "switchblock_off.png");
	resourceManager_.load("explosive", "explosive.png");
	resourceManager_.load("serum", "serum.png");
	resourceManager_.load("player_attacking", "player_attacking.png");
	resourceManager_.load("backgroundtile", "backgroundtile.png");

	resourceManager_.load("level1", "levels/level1.png");
	resourceManager_.load("level2", "levels/level2.png");
	resourceManager_.load("level3", "levels/level3.png");
	resourceManager_.load("level4", "levels/level4.png");
	resourceManager_.load("level5", "levels/level5.png");
	resourceManager_.load("level6", "levels/level6.png");
	resourceManager_.load("level7", "levels/level7.png");
	resourceManager_.load("level8", "levels/level8.png");
	resourceManager_.load("level9", "levels/level9.png");
	resourceManager_.load("level10", "levels/level10.png");

	levels_.push_back(std::unique_ptr<Level>(new Level1(&font)));
	levels_.push_back(std::unique_ptr<Level>(new Level2(&font)));
	levels_.push_back(std::unique_ptr<Level>(new Level3(&font)));
	levels_.push_back(std::unique_ptr<Level>(new Level4(&font)));
	levels_.push_back(std::unique_ptr<Level>(new Level5(&font)));
	levels_.push_back(std::unique_ptr<Level>(new Level6(&font)));
	levels_.push_back(std::unique_ptr<Level>(new Level7(&font)));
	levels_.push_back(std::unique_ptr<Level>(new Level8(&font)));
	levels_.push_back(std::unique_ptr<Level>(new Level9(&font)));
	levels_.push_back(std::unique_ptr<Level>(new Level10(&font)));
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
		//std::cout << "No more levels!" << std::endl;
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