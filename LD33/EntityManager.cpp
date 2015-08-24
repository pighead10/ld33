#include "stdafx.h"
#include "EntityManager.h"
#include "Entity.h"
#include "SFLD.h"
#include "ResourceManager.h"
#include "ParticleEngine.h"

EntityManager::EntityManager(ResourceManager<sf::Texture, std::string>* resourceManager):resourceManager_(resourceManager){
	view = SFLD::window_->getDefaultView();
	in_shake = false;
	shake_timer = 0;
	shake_length = 0;
	deadGuards = 0;
	playerDead = false;

	background.create(SFLD::window_->getSize().x,SFLD::window_->getSize().y);

	//initialise background
	for (int x = 0; x < SFLD::window_->getSize().x; x += TILE_SIZE){
		for (int y = 0; y < SFLD::window_->getSize().y; y += TILE_SIZE){
			sf::Sprite spr(resourceManager_->get("backgroundtile"));
			spr.setPosition(x, y);
			background.draw(spr);
		}
	}
}

EntityManager::~EntityManager() = default;

void EntityManager::addEntity(Entity* entity){
	push_queue_.push_back(std::unique_ptr<Entity>(entity));
}

EntityList* EntityManager::getEntities(){
	return &entities_;
}

void EntityManager::clear(){
	entities_.clear();
	push_queue_.clear();
	deadGuards = 0;
	playerDead = false;
}

void EntityManager::playerDied(){
	playerDead = true;
}

bool EntityManager::isPlayerDead() const{
	return playerDead;
}

sfld::Vector2f EntityManager::convertCoords(sfld::Vector2f tilepos){
	return sfld::Vector2f(tilepos.x*TILE_SIZE + TILE_SIZE / 2, tilepos.y*TILE_SIZE + TILE_SIZE / 2);
}

int EntityManager::getDeadGuards() const{
	return deadGuards;
}

void EntityManager::guardDied(){
	deadGuards++;
}

void EntityManager::update(int frameTime){
	for (auto& it : entities_){
		it->update(frameTime);
	}
	for (auto& it = entities_.begin(); it != entities_.end();){
		if ((*it)->isDestroyed()){
			it = entities_.erase(it);
		}
		else{
			it++;
		}
	}

	for (auto& it : push_queue_){
		entities_.push_back(std::move(it));
	}
	push_queue_.clear();

	if (in_shake){
		float xdisp = (rand() % 21 - 10) / 10.0f;
		float ydisp = (rand() % 21 - 10) / 10.0f;
		view.setCenter(SFLD::window_->getDefaultView().getCenter() + sfld::Vector2f(xdisp*shake_magnitude, ydisp*shake_magnitude));
		SFLD::window_->setView(view);
		shake_timer += frameTime;
		if (shake_timer >= shake_length){
			shake_timer = 0;
			view = SFLD::window_->getDefaultView();
			SFLD::window_->setView(view);
			in_shake = false;
		}
	}
}

void EntityManager::render(sf::RenderTarget* target,ParticleEngine* particleEngine){
	background.display();

	sf::Sprite spr(background.getTexture());
	target->draw(spr);
	particleEngine->renderStatics(target);
	for (auto& it : entities_){
		it->render(target);
	}
}

void EntityManager::screenShake(float magnitude,int time){
	in_shake = true;
	shake_magnitude = magnitude;
	shake_length = time;
	shake_timer = 0;
}