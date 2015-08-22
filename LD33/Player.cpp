#include "stdafx.h"
#include "Player.h"

Player::Player(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f position):speed_(0.5f){
	constructEntity(resourceManager, "player", entityManager, position, true, true, SHAPE_CIRCLE, DYNAMIC_MOVING);
}

void Player::update(int frameTime){
	using namespace sf;
	sfld::Vector2f dir(0, 0);
	if (Keyboard::isKeyPressed(Keyboard::W)){
		dir.y -= 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)){
		dir.y += 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::A)){
		dir.x -= 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)){
		dir.x += 1;
	}
	dir = dir.normalise();
	move(dir, frameTime, speed_);
}