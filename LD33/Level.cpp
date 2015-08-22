#include "stdafx.h"
#include "Level.h"
#include "EntityManager.h"
#include "Wall.h"
#include "Guard.h"
#include "Player.h"
#include "Serum.h"
#include "ParticleEngine.h"
#include "SFLD.h"

Level::Level() = default;
Level::~Level() = default;

void Level::baseEvents(sf::Event evt){
	using namespace sf;
	if (evt.type = Event::KeyPressed){
		if (evt.key.code == Keyboard::R){
			//restart
			startLevel(entityManager_,resourceManager_,particleEngine_);
		}
		else if (evt.key.code == Keyboard::Return){
			advance_level_ = true;
		}
	}
}

void Level::sfmlEvent(sf::Event evt){
	using namespace sf;
	baseEvents(evt);
}

bool Level::getAdvanceLevel() const{
	return advance_level_;
}

void Level::won(){
	advance_level_ = true;
}

void Level::update(int frameTime){
	particleEngine_->update(frameTime);
	entityManager_->update(frameTime);
	if (serum_->hasCollected() && entityManager_->getDeadGuards() <= guard_limit_){
		won();
	}
}

void Level::startLevel(EntityManager* entityManager,ResourceManager<sf::Texture,std::string>* resourceManager,ParticleEngine* particleEngine){
	entityManager_ = entityManager;
	resourceManager_ = resourceManager;
	particleEngine_ = particleEngine;

	entityManager_->clear();
	particleEngine_->clear();
}

void Level::render(sf::RenderTarget* target){
	particleEngine_->renderStatics(target);
	entityManager_->render(target);
	particleEngine_->renderParticles(target);
	
}

void Level::loadFromImage(std::string textureName){
	sf::Image image = resourceManager_->get(textureName).copyToImage();

	//create outside wall
	for (int x = 0; x < SFLD::window_->getSize().x / TILE_SIZE; x++){
		sfld::Vector2f position = EntityManager::convertCoords(sfld::Vector2f(x, -1));
		sfld::Vector2f position2 = EntityManager::convertCoords(sfld::Vector2f(x, (int)(SFLD::window_->getSize().y/TILE_SIZE)));
		entityManager_->addEntity(new Wall(resourceManager_, entityManager_, position));
		entityManager_->addEntity(new Wall(resourceManager_, entityManager_, position2));
	}
	for (int y = 0; y< SFLD::window_->getSize().y / TILE_SIZE; y++){
		sfld::Vector2f position = EntityManager::convertCoords(sfld::Vector2f(-1, y));
		sfld::Vector2f position2 = EntityManager::convertCoords(sfld::Vector2f((int)(SFLD::window_->getSize().x / TILE_SIZE),y));
		entityManager_->addEntity(new Wall(resourceManager_, entityManager_, position));
		entityManager_->addEntity(new Wall(resourceManager_, entityManager_, position2));
	}

	player_ = new Player(resourceManager_, entityManager_, sfld::Vector2f(0, 0),particleEngine_);
	entityManager_->addEntity(player_);

	for (int x = 0; x < image.getSize().x; x++){
		for (int y = 0; y < image.getSize().y; y++){
			sf::Color colour = image.getPixel(x, y);
			sfld::Vector2f position = sfld::Vector2f((float)x*TILE_SIZE+TILE_SIZE/2, (float)y*TILE_SIZE+TILE_SIZE/2);
			if (colour == sf::Color(0, 0, 0)){
				entityManager_->addEntity(new Wall(resourceManager_, entityManager_, position));
			}
			else if (colour == sf::Color(255, 216, 0)){
				entityManager_->addEntity(new Guard(resourceManager_, entityManager_, position, player_, particleEngine_));
			}
			else if (colour == sf::Color(255, 0, 0)){
				player_->setPosition(position);
			}
			else if (colour == sf::Color(0, 255, 0)){
				serum_ = new Serum(resourceManager_, entityManager_, position);
				entityManager_->addEntity(serum_);
			}
		}
	}
}