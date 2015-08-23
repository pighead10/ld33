#include "stdafx.h"
#include "Level.h"
#include "EntityManager.h"
#include "Wall.h"
#include "Guard.h"
#include "Player.h"
#include "Serum.h"
#include "ParticleEngine.h"
#include "SFLD.h"
#include "Explosive.h"

Level::Level() = default;
Level::~Level() = default;

Level::Level(sf::Font* font){
	constructLevel(font);
}

void Level::constructLevel(sf::Font* font){
	font_ = font;
	lostOverlay = sf::RectangleShape(sf::Vector2f(SFLD::window_->getSize().x, SFLD::window_->getSize().y));
	lostOverlay.setFillColor(sf::Color(123, 123, 123, 0));
	lostText1 = sf::Text("YOU DIED!", *font, 70);
	lostText1.setPosition(SFLD::window_->getSize().x / 2 - lostText1.getLocalBounds().width / 2, SFLD::window_->getSize().y / 2 - lostText1.getLocalBounds().height / 2);
	lostText1.setColor(sf::Color::White);
	lostText2 = sf::Text("'R' to restart level", *font, 50);
	lostText2.setPosition(SFLD::window_->getSize().x / 2 - lostText2.getLocalBounds().width / 2, lostText1.getPosition().y + 100);
	lostText2.setColor(sf::Color::White);
	lostText3 = sf::Text("'Enter' to skip level", *font, 50);
	lostText3.setPosition(SFLD::window_->getSize().x / 2 - lostText2.getLocalBounds().width / 2, lostText2.getPosition().y + 70);
	lostText3.setColor(sf::Color::White);

	killOverlay = sf::RectangleShape(sf::Vector2f(SFLD::window_->getSize().x, SFLD::window_->getSize().y));
	killOverlay.setFillColor(sf::Color(123, 123, 123, 0));
	killText1 = sf::Text("YOU KILLED TOO MANY!", *font, 70);
	killText1.setPosition(SFLD::window_->getSize().x / 2 - killText1.getLocalBounds().width / 2, SFLD::window_->getSize().y / 2 - killText1.getLocalBounds().height / 2);
	killText1.setColor(sf::Color::White);
	killText2 = sf::Text("'R' to restart level", *font, 50);
	killText2.setPosition(SFLD::window_->getSize().x / 2 - killText2.getLocalBounds().width / 2, killText1.getPosition().y + 100);
	killText2.setColor(sf::Color::White);
	killText3 = sf::Text("'Enter' to skip level", *font, 50);
	killText3.setPosition(SFLD::window_->getSize().x / 2 - killText2.getLocalBounds().width / 2, killText2.getPosition().y + 70);
	lostText3.setColor(sf::Color::White);
	killText4 = sf::Text("Do you not have a conscience?", *font, 50);
	killText4.setPosition(SFLD::window_->getSize().x / 2 - killText4.getLocalBounds().width / 2, killText3.getPosition().y + 100);
	killText4.setColor(sf::Color::White);
	killText5 = sf::Text("Don't kill more than necessary! (displayed at top of screen)", *font, 20);
	killText5.setPosition(SFLD::window_->getSize().x / 2 - killText5.getLocalBounds().width / 2, killText4.getPosition().y + 70);
	killText5.setColor(sf::Color::White);

	wonText1 = sf::Text("YOU SUCCEEDED!", *font, 70);
	wonText1.setPosition(SFLD::window_->getSize().x / 2 - wonText1.getLocalBounds().width / 2, SFLD::window_->getSize().y / 2 - wonText1.getLocalBounds().height / 2);
	wonText1.setColor(sf::Color::White);
	wonText2 = sf::Text("'Y' to advance", *font, 50);
	wonText2.setPosition(SFLD::window_->getSize().x / 2 - wonText2.getLocalBounds().width / 2, wonText1.getPosition().y + 100);
	wonText2.setColor(sf::Color::White);

	messageText = sf::Text("", *font, 50);
	messageText.setColor(sf::Color::White);
}

void Level::displayMessage(std::string text){
	messageText.setString(text);
	messageText.setPosition(SFLD::window_->getSize().x / 2 - messageText.getLocalBounds().width / 2, SFLD::window_->getSize().y / 2 - messageText.getLocalBounds().height / 2);
	disp_message = true;
	messageTimer = 0;
}

void Level::baseEvents(sf::Event evt){
	using namespace sf;
	if (evt.type == Event::KeyPressed){
		
		if (evt.key.code == Keyboard::R){
			//restart
			startLevel(entityManager_,resourceManager_,particleEngine_);
		}
		else if (evt.key.code == Keyboard::Return){
			advance_level_ = true;
		}
		else if (evt.key.code == Keyboard::Y){
			if (finished){
				advance_level_ = true;
			}
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
	player_->immune = true;
	finished = true;
}

void Level::lost(){
	gameLost = true;
}

void Level::overkilled(){
	if (!overkill){
		overkill = true;
		killTimer = 0;
	}
}

void Level::update(int frameTime){
	particleEngine_->update(frameTime);
	//if (!finished){
		entityManager_->update(frameTime);
	//}
	if (serum_->hasCollected()){
		if (entityManager_->getDeadGuards() <= guard_limit_){
			won();
		}
		else{
			overkilled();
		}
	}
	if (entityManager_->isPlayerDead()){
		lost();
	}
	if (gameLost){
		lostTimer += frameTime;
		lostTimer = (lostTimer > 500 ? 500 : lostTimer);
		lostOverlay.setFillColor(sf::Color(lostOverlay.getFillColor().r, lostOverlay.getFillColor().g, lostOverlay.getFillColor().b, 100.0f * (lostTimer / 500.0f)));
	}
	if (overkill){
		killTimer += frameTime;
		killTimer = (killTimer > 500 ? 500 : killTimer);
		killOverlay.setFillColor(sf::Color(killOverlay.getFillColor().r, killOverlay.getFillColor().g, killOverlay.getFillColor().b, 100.0f * (killTimer / 500.0f)));
	}
	if (disp_message){
		messageTimer += frameTime;
		int length = 2000;
		if (messageTimer >= length){
			int t = messageTimer - length;
			messageText.setPosition(messageText.getPosition().x,
				(SFLD::window_->getSize().y / 2 - messageText.getLocalBounds().height / 2) - (t / 500.0f)*(SFLD::window_->getSize().y / 2 - messageText.getLocalBounds().height / 2));
			if (messageTimer >= length+600){
				disp_message = false;
			}
		}
	}
}

void Level::baseStartLevel(EntityManager* entityManager, ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine){
	entityManager_ = entityManager;
	resourceManager_ = resourceManager;
	particleEngine_ = particleEngine;

	entityManager_->clear();
	particleEngine_->clear();

	finished = false;
	gameLost = false;
	lostTimer = 0;
	advance_level_ = false;
	disp_message = false;
	messageTimer = 0;
	overkill = false;
}

void Level::startLevel(EntityManager* entityManager,ResourceManager<sf::Texture,std::string>* resourceManager,ParticleEngine* particleEngine){
	baseStartLevel(entityManager, resourceManager, particleEngine);
}

void Level::render(sf::RenderTarget* target){
	particleEngine_->renderStatics(target);
	entityManager_->render(target);
	particleEngine_->renderParticles(target);
	
	if (gameLost){
		target->draw(lostOverlay);
		target->draw(lostText1);
		target->draw(lostText2);
		target->draw(lostText3);
	}
	if (finished){
		target->draw(wonText1);
		target->draw(wonText2);
	}
	if (overkill){
		target->draw(killOverlay);
		target->draw(killText1);
		target->draw(killText2);
		target->draw(killText3);
		target->draw(killText4);
		target->draw(killText5);
	}

	if (disp_message){
		target->draw(messageText);
	}
	
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
			else if (colour == sf::Color(128, 128, 128)){
				entityManager_->addEntity(new Explosive(resourceManager_, entityManager_, position, particleEngine_));
			}
		}
	}
}